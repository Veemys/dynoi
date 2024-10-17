#include "pch.h"

#include "Vector2DTest.h"
#include "SIteTest.h"
#include "EdgeTest.h"
#include "CellTest.h"
#include "VertexTest.h"
#include "MathTest.h"
#include "TriangleTest.h"

int main(int arc, char** argv)
{
	::testing::InitGoogleTest(&arc, argv);

	return RUN_ALL_TESTS();
}