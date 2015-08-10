//SG函数
//sprague_grundy.cpp

//A和B两人从有向图的起始点开始轮流将一颗棋子沿着有向边移动，每次至少移动1个节点
//最后到达终点的人获胜

//1)模型
//本文之前所讲的三种博弈都属于公正组合游戏(Impartial Combinatorial Games)
//这是一种两人博弈，在博弈中双方都能看到完整的状态信息，任何操作对双方都有相同的效果
//这种博弈的每个局势都可以抽象为一种状态点
//两人从起始状态点出发，每次改变状态点进而得到下一个状态点，到达最终状态点的人获胜
//将这样一个过程抽象为两人从有向图的起始点开始轮流移动一颗棋子到终点的数学模型
//注意这个有向图中不存在环，因为一个状态不可能经过一系列的转换后又回到自己原本的状态
//
//2)状态点
//在有向图的模型下，每个节点都可以看一种状态点
//并且也存在最终态(最终局势)，必败态(奇异局势)，必胜态(非奇异局势)
//最终态即为有向图的终点end
//设图中某个节点i有一条边可以到达有向图终点end，即有向图终点end是节点i的邻节点
//则面临该节点i的人必胜，面临有向图终点end的人必输
//而所有这样的节点i，即可以一步到达有向图终点end的节点i都是奇异局势，必败态
//为了方便，本文中将节点i称为父节点，或者前驱节点
//而以节点i为起点的边，指向的有向图终点称为节点i的孩子节点，或者后继节点
//
//更进一步的我们可以得到结论：
//若一个节点是必败态P，其所有后继节点都是必胜态N，没有必败态P的后继节点
//若一个节点是必胜态N，则必有一个(一些)必败态P的后继节点，也存在其他必胜态N的后继节点
//博弈的核心就在于判断出一个必胜态N节点的所有后继节点中哪个(哪些)是必败态P的后继节点
//选择必败态P的后继节点移动，即可使对方面临必败态P，从而最终使自己获胜
//
//3)Sprague-Grundy(SG)函数
//设mex(Minimal Excludant)是非负整数集合上的运算，返回该集合中不存在的最小非负整数
//比如集合S={0, 1, 2, 4}，则mex(S) = 3，集合S={2, 3, 4}，则mex(S) = 0
//将有向图中节点i的Sprague-Grundy函数记作sg(i) = mex{g(j) | 节点j是节点i的后继节点}
//sg值为0的节点是最终态，必败态，sg值不为0的节点是必胜态
//
//4)函数性质
//有向图终点end的sg(end) = 0，因为该节点没有后继节点
//有向图中节点i是必败态P当且仅当sg(i) = 0，它的所有后继节点的sg值都不为0
//有向图中节点i是必胜态N当且仅当sg(i) != 0，它的后继节点中有些sg值为0，有些不为0
//节点的sg值体现出博弈中必败态和必胜态的关系
//并且有向图中后继节点的sg值总是比前驱节点的sg值小，sg值随着移动总是减小，而不会不变
//这个性质对应本文之前三种博弈中至少取1个物品的情况，而不会出现物品数不变的情况
//
//5)有向图模型应用
//本文中的有向图模型实际对应于本文之前所说的一堆物品
//有向图终点end是物品被取空的最终态，有向图起点beg是物品堆的起始状态
//取1个物品是在有向图中沿着有向边移动1个节点，1条边的距离
//取m个物品是在有向图中沿着有向边移动m个节点，m条边的距离
//
//当有n个这样的有向图，每个图的起点beg处都有一颗棋子
//A和B两人轮流移动n个有向图上的其中一颗棋子(一次只能移动一颗棋子)
//最后让所有棋子都到达各自有向图中的终点的人获胜
//这个模型即可对应尼姆博弈中的n堆物品，每次取至少1个物品，多则不限的情况
//
//当n颗棋子各自的sg值的状态是(sg(i1), sg(i2), sg(i3), ..., sg(in))
//其中i1是第1个有向图中的节点，i2是第2个有向图中的节点，依次类推
//设@为异或运算
//一个状态是必败态当且仅当sg(i1) @ sg(i2) @ ... @ sg(in) = 0
//一个状态是必胜态当且仅当sg(i1) @ sg(i2) @ ... @ sg(in) != 0
//这个定理与尼姆博弈中的定理相对应

//bool sprague_grundy(int *a, int n, int& idx, int& get)
