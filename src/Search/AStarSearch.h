#pragma once
#include "Util.h"
#include <climits>
#include <vector>
#ifndef MAX
#define MAX 128
#endif
#ifndef INF
#define INF INT_MAX
#endif

/**
 * AStarSearch  A*搜索
 * @param n     行
 * @param m     列
 * @param beg   起点座标
 * @param end   终点座标
 * @return      从起点到终点的座标路径
 */
std::vector<BfsNode> AStarSearch(int block[MAX][MAX], int n, int m,
                                 const BfsNode &beg, const BfsNode &end);

