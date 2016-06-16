//
//  voxel.cpp
//  Lab3
//

#include "voxel.h"
#include <cstdlib>
#include <cstdint>
#include <cassert>
#include "main.h"
#include <algorithm>
#include <vector>

struct voxelWorld {
	uint32_t header;
	float voxelSize;
	uint64_t numVoxelsGrids;
	float minbounds[4];
	float maxbounds[4];
	uint64_t *morton;
	uint64_t *grid;
};

class point3d {
public:
	point3d() {}
	point3d(float a, float b, float c) :x(a), y(b), z(c) {}
	float x, y, z;
};

voxelWorld LoadData(const char *);
void Draw(voxelWorld w, const char *);

void ImportAndExportVoxelMap(const char *input, const char *output)
{
	voxelWorld w = LoadData(input);
	Draw(w, output);
}


void GetCoordsForIndex(size_t i, size_t& x, size_t& y, size_t& z)
{
	x = i >> 4;
	y = (i & 0x0F) >> 2;
	z = (i & 0x03);
}

point3d GetVoxelCoordinate(uint64_t morton, float voxelSize, float minbounds[4])
{
	point3d pt(DecodeMorton3X(morton), DecodeMorton3Y(morton), DecodeMorton3Z(morton));
	pt.x*=voxelSize*4;
	pt.x += minbounds[0];
	pt.y*=voxelSize*4;
	pt.y += minbounds[1];
	pt.z*=voxelSize*4;
	pt.z += minbounds[2];
	//const size_t ix = static_cast<size_t>(floorf((coords.x - mBounds.MinX()) / (voxelSize * 4)));
	return pt;
}

voxelWorld LoadData(const char *map)
{
	FILE *f = fopen(map, "r");
	if (f == 0)
	{
		printf("Error opening file\n");
		exit(0);
	}
	voxelWorld w;
	fread(&w.header, sizeof(w.header), 1, f);
	printf("Header is 0x%lX\n", w.header);
	fread(&w.voxelSize, sizeof(w.voxelSize), 1, f);
	//printf("Voxel size is %f\n", w.voxelSize);
	fread(&w.numVoxelsGrids, sizeof(w.numVoxelsGrids), 1, f);
	//printf("%llu voxel grids to follow\n", w.numVoxelsGrids);
	fread(w.minbounds, sizeof(w.minbounds[0]), 4, f);
	fread(w.maxbounds, sizeof(w.maxbounds[0]), 4, f);
	w.morton = new uint64_t[w.numVoxelsGrids];
	w.grid = new uint64_t[w.numVoxelsGrids];
	for (int x = 0; x < w.numVoxelsGrids; x++)
	{
		size_t count = fread(&w.morton[x], sizeof(w.morton[x]), 1, f);
		assert(count == 1);
		count = fread(&w.grid[x], sizeof(w.grid[x]), 1, f);
		assert(count == 1);
	}
	
	fclose(f);
	return w;
}


void Draw(voxelWorld w, const char *map)
{
	std::vector<bool> layer;
	FILE *f = fopen(map, "w+");
	if (f == 0)
	{
		printf("Errror - can't open output map\n");
		exit(0);
	}
	uint64_t width = (w.maxbounds[0]-w.minbounds[0])/w.voxelSize;
	uint64_t depth = (w.maxbounds[2]-w.minbounds[2])/w.voxelSize;
	int factor = 1/w.voxelSize;
	for (int y = w.maxbounds[1]*factor; y >= w.minbounds[1]*factor; y--)
	{
		layer.clear();
		layer.resize(width*depth);
		for (int x = 0; x < w.numVoxelsGrids; x++)
		{
			point3d p = GetVoxelCoordinate(w.morton[x], w.voxelSize, w.minbounds);
			for (int i = 0; i < 64; i++)
			{
				size_t a, b, c;
				GetCoordsForIndex(i, a, b, c);
				if ((y == p.y+b) && (w.grid[x]>>i)&1) // blocked
				{
					layer[(p.x*factor+a-w.minbounds[0]*factor)+width*(p.z*factor+c-w.minbounds[2]*factor)] = true;
				}
			}
		}
		for (int x = 0; x < width; x++)
		{
			for (int z = 0; z < depth; z++)
			{
				if (layer[x+z*width])
					fprintf(f, "*");
				else
					fprintf(f, ".");
			}
			fprintf(f, "\n");
		}
		fprintf(f, "\n");
	}
	fclose(f);
}