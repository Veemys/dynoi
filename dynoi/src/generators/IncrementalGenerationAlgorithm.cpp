#include "IncrementalGenerationAlgorithm.h"

#include "../kernel/Boundary.h"
#include "../kernel/Vector2D.h"
#include "../kernel/Site.h"
#include "../kernel/Vertex.h"
#include "../kernel/Edge.h"
#include "../kernel/Cell.h"
#include "../kernel/VoronoiDiagram.h"
#include "../mathem/Math.h"
#include "../mathem/Triangle.h"

std::shared_ptr<VoronoiDiagram> IncrementalGenerationAlgorithm::apply(std::vector<Site>& sites, Boundary& boundary)
{
    std::shared_ptr<VoronoiDiagram> vd(std::make_shared<VoronoiDiagram>());
    
    initFirstCell(boundary, *vd, sites[0]);
    for (int siteIndex = 1; siteIndex < sites.size(); ++siteIndex)
    {
        addCell(*vd, sites[siteIndex]);
    }

    return vd;
}

void IncrementalGenerationAlgorithm::initFirstCell(Boundary& boundary, VoronoiDiagram& vd, Site& firstSite)
{
    std::shared_ptr<Cell> firstCell(std::make_shared<Cell>(firstSite));
    for (auto edge = boundary.edges().begin(); edge != boundary.edges().end(); ++edge)
    {
        firstCell->addEdge(*edge);
        (*edge)->addCells(std::make_pair(firstCell, nullptr));
    }
    vd.addCell(firstCell);
}

void IncrementalGenerationAlgorithm::addCell(VoronoiDiagram& vd, Site& site)
{
    std::shared_ptr<Cell> newCell(std::make_shared<Cell>(site));
    std::shared_ptr<Cell> nearestCell(findNearestCell(vd, site));
    std::set<std::shared_ptr<Cell>> processedCells;
    std::set<std::shared_ptr<Cell>> nearCells;
    for (std::shared_ptr<Cell> nextCell = nearestCell;;)
    {
        processedCells.emplace(nextCell);
        std::pair<std::shared_ptr<Edge>, std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>>> newEdgeAndIntersectedEdges = createDividingEdge(newCell, nextCell);
        std::shared_ptr<Edge> newEdge = newEdgeAndIntersectedEdges.first;
        std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>> intersectedEdges = newEdgeAndIntersectedEdges.second;
        nextCell = getNextCell(intersectedEdges, newEdge, processedCells, nearCells, newCell);
        if (nextCell == nullptr)
        {
            break;
        }
    }
    changeDividedEdges(newCell);
    deleteAllEdgeInsideNewCell(newCell);

    vd.addCell(newCell);
}

std::shared_ptr<Cell> IncrementalGenerationAlgorithm::findNearestCell(VoronoiDiagram& vd, Site& site)
{
    double distanceToNearestCell = std::numeric_limits<double>::max();
    std::shared_ptr<Cell> nearestCell = nullptr;
    for (auto& cell : vd.cells())
    {
        double currentDistance = (cell->site().coord() - site.coord()).length();
        if (currentDistance < distanceToNearestCell)
        {
            nearestCell = cell;
            distanceToNearestCell = currentDistance;
        }
    }
    return nearestCell;
}

std::pair<std::shared_ptr<Edge>, std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>>> IncrementalGenerationAlgorithm::createDividingEdge(
    std::shared_ptr<Cell> newCell, std::shared_ptr<Cell> nextCell)
{
    Vector2D direction = (nextCell->site().coord() - newCell->site().coord()).getNorm();
    Vector2D center = (nextCell->site().coord() + newCell->site().coord()) / 2.0;
    Vector2D edgeDirection = Vector2D(-direction.y(), direction.x());
    edgeDirection.normalize();

    std::shared_ptr<Edge> startEdge = nullptr;
    std::shared_ptr<Vertex> start = nullptr;
    std::shared_ptr<Edge> endEdge = nullptr;
    std::shared_ptr<Vertex> end = nullptr;
    
    std::multimap<double, std::pair<std::shared_ptr<Edge>, Vector2D>> fucking;
    std::set<std::shared_ptr<Edge>> deletedEdges;
    for (auto& edge : nextCell->edges())
    {
        if (deletedEdges.contains(edge))
            continue;

        const double newStraightElongationFactor = 1000.0;
        std::pair<Vector2D, Vector2D> newEdgeStraight =
            std::make_pair(center + newStraightElongationFactor * edgeDirection, center - newStraightElongationFactor * edgeDirection);
        std::pair<Vector2D, Vector2D> currentEdgeStraight = std::make_pair(edge->start(), edge->end());
        Vector2D straightIntersection = Math::straightsIntersection(newEdgeStraight, currentEdgeStraight);

        if (Math::isTheSamePoints(straightIntersection, edge->start()))
        {
            if (start != nullptr)
            {
                end = edge->getVertices().first;
            }
            else
            {
                start = edge->getVertices().first;
            }
            const auto& edgesFromVertex = edge->getVertices().first->getEdges();
            std::set<std::shared_ptr<Edge>> shouldBeProcessedEdges;
            for (auto& edgeFromVertex : edgesFromVertex)
            {
                if (edgeFromVertex->getParentCells().first == nextCell || edgeFromVertex->getParentCells().second == nextCell)
                {
                    shouldBeProcessedEdges.insert(edgeFromVertex);
                }
            }
            for (auto& shouldBeProcessedEdge : shouldBeProcessedEdges)
            {
                if (Math::pointsLayFromOneSide(shouldBeProcessedEdge->center(), newCell->site().coord(), newEdgeStraight))
                {
                    nextCell->eraseEdge(shouldBeProcessedEdge);
                    deletedEdges.insert(shouldBeProcessedEdge);
                    newCell->addEdge(shouldBeProcessedEdge);
                    if (shouldBeProcessedEdge->getParentCells().first == nextCell)
                    {
                        shouldBeProcessedEdge->addCell(newCell, Edge::LEFT);
                    }
                    else if (shouldBeProcessedEdge->getParentCells().second == nextCell)
                    {
                        shouldBeProcessedEdge->addCell(newCell, Edge::RIGHT);
                    }
                }
            }
            continue;
        }
        else if (Math::isTheSamePoints(straightIntersection, edge->end()))
        {
            if (start != nullptr)
            {
                end = edge->getVertices().second;
            }
            else
            {
                start = edge->getVertices().second;
            }
            const auto& edgesFromVertex = edge->getVertices().second->getEdges();
            std::set<std::shared_ptr<Edge>> shouldBeProcessedEdges;
            for (auto& edgeFromVertex : edgesFromVertex)
            {
                if (edgeFromVertex->getParentCells().first == nextCell || edgeFromVertex->getParentCells().second == nextCell)
                {
                    shouldBeProcessedEdges.insert(edgeFromVertex);
                }
            }
            for (auto& shouldBeProcessedEdge : shouldBeProcessedEdges)
            {
                if (Math::pointsLayFromOneSide(shouldBeProcessedEdge->center(), newCell->site().coord(), newEdgeStraight))
                {
                    nextCell->eraseEdge(shouldBeProcessedEdge);
                    deletedEdges.insert(shouldBeProcessedEdge);
                    newCell->addEdge(shouldBeProcessedEdge);
                    if (shouldBeProcessedEdge->getParentCells().first == nextCell)
                    {
                        shouldBeProcessedEdge->addCell(newCell, Edge::LEFT);
                    }
                    else if (shouldBeProcessedEdge->getParentCells().second == nextCell)
                    {
                        shouldBeProcessedEdge->addCell(newCell, Edge::RIGHT);
                    }
                }
            }
            continue;
        }

        double distance = (newCell->site().coord() - straightIntersection).length();
        if (Math::pointLayInsideSegment(straightIntersection, std::make_pair(edge->getStartVertex().coord(), edge->getEndVertex().coord())))
        {
            fucking.emplace(distance, std::make_pair(edge, straightIntersection));
        }
    }

    if (!fucking.empty())
    {
        auto fuckingIter(fucking.begin());
        if (start == nullptr)
        {
            startEdge = fuckingIter->second.first;
            if (intersectedOldEdgesToNewVerticesLinks_.contains(startEdge))
            {
                start = intersectedOldEdgesToNewVerticesLinks_.at(startEdge);
            }
            else
            {
                start = std::make_shared<Vertex>(fuckingIter->second.second);
                intersectedOldEdgesToNewVerticesLinks_.emplace(startEdge, start);
            }
        }

        ++fuckingIter;
        if ((fuckingIter == fucking.end()) && end == nullptr)
        {
            --fuckingIter;
            endEdge = fuckingIter->second.first;
            if (intersectedOldEdgesToNewVerticesLinks_.contains(endEdge))
            {
                end = intersectedOldEdgesToNewVerticesLinks_.at(endEdge);
            }
            else
            {
                end = std::make_shared<Vertex>(fuckingIter->second.second);
                intersectedOldEdgesToNewVerticesLinks_.emplace(endEdge, end);
            }
        }
        if (fuckingIter != fucking.end())
        {
            if (end == nullptr)
            {
                endEdge = fuckingIter->second.first;
                if (intersectedOldEdgesToNewVerticesLinks_.contains(endEdge))
                {
                    end = intersectedOldEdgesToNewVerticesLinks_.at(endEdge);
                }
                else
                {
                    end = std::make_shared<Vertex>(fuckingIter->second.second);
                    intersectedOldEdgesToNewVerticesLinks_.emplace(endEdge, end);
                }
            }
        }
    }
    
    std::shared_ptr<Edge> newEdge(createEdge(start, end, std::make_pair(newCell, nextCell)));
    std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>> intersectedEdges(std::make_pair(startEdge, endEdge));

    return std::make_pair(newEdge, intersectedEdges);
}

bool IncrementalGenerationAlgorithm::someVertexIntersectedAndAdded(Vector2D& intersection, const std::shared_ptr<Edge>& edge,
    std::set<std::shared_ptr<Vertex>>& intersectedVertices)
{
    std::shared_ptr<Vertex> startVertex = edge->getVertices().first;
    std::shared_ptr<Vertex> endVertex = edge->getVertices().second;
    if (std::abs((intersection - startVertex->coord()).length()) <= Math::eps)
    {
        intersectedVertices.insert(startVertex);
        return true;
    }
    else if (std::abs((intersection - endVertex->coord()).length()) <= Math::eps)
    {
        intersectedVertices.insert(endVertex);
        return true;
    }
    return false;
}

std::shared_ptr<Edge> IncrementalGenerationAlgorithm::createEdge(std::shared_ptr<Vertex> start, std::shared_ptr<Vertex> end,
    std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>> parentCells)
{
    std::shared_ptr<Edge> newEdge(std::make_shared<Edge>(start, end));
    start->addEdge(newEdge);
    end->addEdge(newEdge);
    newEdge->addCells(parentCells);
    parentCells.first->addEdge(newEdge);
    parentCells.second->addEdge(newEdge);
    
    return newEdge;
}

std::shared_ptr<Cell> IncrementalGenerationAlgorithm::getNextCell(
    std::pair<std::shared_ptr<Edge>, std::shared_ptr<Edge>>& intersectedEdges,
    std::shared_ptr<Edge> newEdge,
    std::set<std::shared_ptr<Cell>>& processedCells,
    std::set<std::shared_ptr<Cell>>& nearCells,
    std::shared_ptr<Cell> newCell)
{
    if (intersectedEdges.first != nullptr)
    {
        nearCells.emplace(intersectedEdges.first->getParentCells().first);
        nearCells.emplace(intersectedEdges.first->getParentCells().second);
    }
    else
    {
        std::cout << "first intersected edges was nullptr\n";
    }

    if (intersectedEdges.second != nullptr)
    {
        nearCells.emplace(intersectedEdges.second->getParentCells().first);
        nearCells.emplace(intersectedEdges.second->getParentCells().second);
    }
    else
    {
        std::cout << "second intersected edges was nullptr\n";
    }

    for (auto& cell : nearCells)
    {
        if (cell != nullptr && !processedCells.contains(cell))
        {
            return cell;
        }
    }

    return nullptr;
}

void IncrementalGenerationAlgorithm::changeDividedEdges(std::shared_ptr<Cell> newCell)
{
    for (auto& oldEdgeNewVertexLink : intersectedOldEdgesToNewVerticesLinks_)
    {
        std::shared_ptr<Edge> intersectedEdge(oldEdgeNewVertexLink.first);
        std::shared_ptr<Vertex> newVertex(oldEdgeNewVertexLink.second);
        std::shared_ptr<Vertex> oldStartVertex(intersectedEdge->getVertices().first);
        std::shared_ptr<Vertex> oldEndVertex(intersectedEdge->getVertices().second);

        bool isBoundaryEdge = ((intersectedEdge->getParentCells().first == nullptr) || (intersectedEdge->getParentCells().second == nullptr));
        if (isBoundaryEdge)
        {
            double distanceFromNewCellToStart = (intersectedEdge->getStartVertex().coord() - newCell->site().coord()).length();
            double distanceFromNewCellToEnd = (intersectedEdge->getEndVertex().coord() - newCell->site().coord()).length();

            std::shared_ptr<Edge> dividingEdge = nullptr;
            for (auto& newCellEdge : newCell->edges())
            {
                if (newCellEdge->getVertices().first == newVertex ||
                    newCellEdge->getVertices().second == newVertex)
                {
                    dividingEdge = newCellEdge;
                    break;
                }
            }

            if (vertexLayFromNewCellSide(oldEndVertex, dividingEdge, newCell))
            {
                std::shared_ptr<Edge> newEdge(std::make_shared<Edge>(oldEndVertex, newVertex));
                oldEndVertex->removeEdge(intersectedEdge);
                oldEndVertex->addEdge(newEdge);
                newVertex->addEdge(newEdge);

                intersectedEdge->replaceEndVertex(newVertex);
                newVertex->addEdge(intersectedEdge);

                newCell->addEdge(newEdge);
                newEdge->addCells(std::make_pair(newCell, nullptr));

                // check other boundary edges (not intersected)
                // need to rework for complex boundary in future
                for (auto& edge : oldEndVertex->getEdges())
                {
                    if (edge != newEdge &&
                        (edge->getParentCells().first == nullptr || edge->getParentCells().second == nullptr) &&
                        !intersectedOldEdgesToNewVerticesLinks_.contains(edge))
                    {
                        auto& ownerCell = edge->getParentCells().first == nullptr ? edge->getParentCells().second : edge->getParentCells().first;
                        ownerCell->eraseEdge(edge);
                        edge->eraseParentCells();
                        
                        newCell->addEdge(edge);
                        edge->addCells(std::make_pair(newCell, nullptr));
                        // need check next edges
                    }
                }
            }
            else
            {
                std::shared_ptr<Edge> newEdge(std::make_shared<Edge>(oldStartVertex, newVertex));
                oldStartVertex->removeEdge(intersectedEdge);
                oldStartVertex->addEdge(newEdge);
                newVertex->addEdge(newEdge);

                intersectedEdge->replaceStartVertex(newVertex);
                newVertex->addEdge(intersectedEdge);

                newCell->addEdge(newEdge);
                newEdge->addCells(std::make_pair(newCell, nullptr));

                // check other boundary edges (not intersected)
                // ?? need to rework for complex boundary in future
                for (auto& edge : oldStartVertex->getEdges())
                {
                    if (edge != newEdge &&
                        (edge->getParentCells().first == nullptr || edge->getParentCells().second == nullptr) &&
                        !intersectedOldEdgesToNewVerticesLinks_.contains(edge))
                    {
                        auto& ownerCell = edge->getParentCells().first == nullptr ? edge->getParentCells().second : edge->getParentCells().first;
                        ownerCell->eraseEdge(edge);
                        edge->eraseParentCells();

                        newCell->addEdge(edge);
                        edge->addCells(std::make_pair(newCell, nullptr));
                        // need check next edges
                    }
                }
            }
        }
        else
        {
            if (vertexLayInsideCell(oldStartVertex, newCell))
            {
                intersectedEdge->replaceStartVertex(newVertex);
                newVertex->addEdge(intersectedEdge);
            }
            else if (vertexLayInsideCell(oldEndVertex, newCell))
            {
                intersectedEdge->replaceEndVertex(newVertex);
                newVertex->addEdge(intersectedEdge);
            }
        }
    }

    intersectedOldEdgesToNewVerticesLinks_.clear();
}

bool IncrementalGenerationAlgorithm::vertexLayFromNewCellSide(std::shared_ptr<Vertex> vertex, std::shared_ptr<Edge> dividingEdge, std::shared_ptr<Cell> newCell)
{
    Vector2D edgeStart = dividingEdge->start();
    Vector2D edgeCenter = dividingEdge->center();
    
    Vector2D fromEdgeStartToEdgeCenter = (edgeCenter - edgeStart).getNorm();
    Vector2D fromEdgeStartToCell = (newCell->site().coord() - edgeStart).getNorm();
    Vector2D fromEdgeStartToVertex = (vertex->coord() - edgeStart).getNorm();
    
    double A = (fromEdgeStartToEdgeCenter.x() * fromEdgeStartToCell.y() - fromEdgeStartToEdgeCenter.y() * fromEdgeStartToCell.x());
    double B = (fromEdgeStartToEdgeCenter.x() * fromEdgeStartToVertex.y() - fromEdgeStartToEdgeCenter.y() * fromEdgeStartToVertex.x());
    return A * B > 0;
}

void IncrementalGenerationAlgorithm::deleteAllEdgeInsideNewCell(std::shared_ptr<Cell> newCell)
{
    for (auto& newCellEdge : newCell->edges())
    {
        std::pair<std::shared_ptr<Cell>, std::shared_ptr<Cell>> parentCells(newCellEdge->getParentCells());
        std::shared_ptr<Cell> neighbourCell(parentCells.first == newCell ? parentCells.second : parentCells.first);
        if (neighbourCell == nullptr)
        {
            continue;
        }
        std::vector<std::shared_ptr<Edge>> shouldDeletedEdges;
        for (auto& neighbourCellEdge : neighbourCell->edges())
        {
            if (edgeLayInsideCell(neighbourCellEdge, newCell) && !newCell->edges().contains(neighbourCellEdge))
            {
                shouldDeletedEdges.push_back(neighbourCellEdge);
            }
        }

        for (auto& edge : shouldDeletedEdges)
        {
            auto& parentCellsFromNeighbourCellEdge = edge->getParentCells();
            if (parentCellsFromNeighbourCellEdge.first != nullptr)
            {
                parentCellsFromNeighbourCellEdge.first->eraseEdge(edge);
            }
            if (parentCellsFromNeighbourCellEdge.second != nullptr)
            {
                parentCellsFromNeighbourCellEdge.second->eraseEdge(edge);
            }
            edge->eraseParentCells();
        }
    }
}

bool IncrementalGenerationAlgorithm::edgeLayInsideCell(std::shared_ptr<Edge> edge, std::shared_ptr<Cell> cell)
{
    const Vector2D& start = edge->start();
    const Vector2D& end = edge->end();
    auto vertices = edge->getVertices();
    bool startLayInsideCell(false);
    bool endLayInsideCell(false);
    for (auto& cellEdge : cell->edges())
    {
        Triangle tr(cell->site().coord(),
            cellEdge->start(),
            cellEdge->end());
        if (vertexLayInsideCell(vertices.first, cell))
        {
            startLayInsideCell = true;
        }
        if (vertexLayInsideCell(vertices.second, cell))
        {
            endLayInsideCell = true;
        }
    }

    return (startLayInsideCell && endLayInsideCell);
}

bool IncrementalGenerationAlgorithm::vertexLayInsideCell(std::shared_ptr<Vertex> vertex, std::shared_ptr<Cell> cell)
{
    double distanceFromVertexToCell = (cell->site().coord() - vertex->coord()).length();
    for (auto& edge : vertex->getEdges())
    {
        auto& cells = edge->getParentCells();

        double distanceFromVertexToOwnerFirstCell = 0.0;
        double distanceFromVertexToOwnerSecondCell = 0.0;
        if (cells.first == nullptr)
        {
            distanceFromVertexToOwnerFirstCell = std::numeric_limits<double>::max();
        }
        else
        {
            distanceFromVertexToOwnerFirstCell = (cells.first->site().coord() - vertex->coord()).length();
        }
        if (cells.second == nullptr)
        {
            distanceFromVertexToOwnerSecondCell = std::numeric_limits<double>::max();
        }
        else
        {
            distanceFromVertexToOwnerSecondCell = (cells.second->site().coord() - vertex->coord()).length();
        }

        if ((distanceFromVertexToCell > distanceFromVertexToOwnerFirstCell) ||
            (distanceFromVertexToCell > distanceFromVertexToOwnerSecondCell))
        {
            return false;
        }
    }

    return true;
}