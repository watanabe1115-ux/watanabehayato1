#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

// 深さ優先探索本体
void dfs(int StartingRoom){
	int listed[N];  // 0 未, 1 済
	int stack[N*N];
	int stacktop = 0;
    
    int CurrentRoom;
    int RoomToCheck;

	int visited[N]; // 列挙順を記録するための配列
	int num_visited = 0; // 記録済の頂点数

	for (RoomToCheck = 0; RoomToCheck < N; RoomToCheck++)
		listed[RoomToCheck] = 0;
	
	printf("深さ優先探索を 頂点%d から開始します．\n", StartingRoom);
    // StartingRoomをスタックに積む
    stack[stacktop] = StartingRoom;
    stacktop++;

	// スタックに処理対象がある限り作業を継続
	while (stacktop > 0) {
		printf("現在のスタック： 長さ %d, スタックトップは %d\n", stacktop, stack[stacktop - 1]);
		{int i; for (i = 0; i < stacktop; i++) printf("%d ", stack[i]); printf("\n");}

        // スタックから１つ降ろして処理開始（スタックからは削除）
		printf("スタックトップの頂点 %d をスタックから降ろして処理を開始します．\n", stack[stacktop - 1]);
		CurrentRoom = stack[stacktop - 1];
        stacktop--;

		if (listed[CurrentRoom] == 0) {
			// 処理済みであることを記録
			printf("頂点 %d をこれ以降は列挙済として扱います．\n", CurrentRoom);
			listed[CurrentRoom] = 1;
			// 計上（列挙）順を記録
			visited[num_visited] = CurrentRoom;
			num_visited++;

        	// 次にどの頂点を列挙していくか検討
			for (RoomToCheck = N-1; RoomToCheck >= 0; RoomToCheck--) {
   				if (edge[CurrentRoom][RoomToCheck] == 0) {
					printf("  (頂点 %d にて) 頂点 %d は隣接していませんでした‥\n", CurrentRoom, RoomToCheck);
				} else if (listed[RoomToCheck] != 0) {
					printf("  (頂点 %d にて) 頂点 %d は隣接はしていますがすでに処理済でした‥\n", CurrentRoom, RoomToCheck);
        		} else {         
					printf("  (頂点 %d にて) まだ処理したことのない頂点 %d が隣接しているので、スタックに積み上げます．\n", CurrentRoom, RoomToCheck);
               		// RoomToCheckをスタックに積む
					stack[stacktop] = RoomToCheck;
               		stacktop++;
				}
			}
		}
	}
	printf("処理待ち行列に何も残っていないので深さ優先探索を終了します．\n");

	printf("深さ優先探索による頂点の列挙．\n");
	for (CurrentRoom = 0; CurrentRoom < N; CurrentRoom++)
		printf("%d ", visited[CurrentRoom]);
    printf("\n");

	return;
}

int main(int argc, char *argv[]){
    int startnode = 0;
    if (argc == 1) {
        printf("指定がなかったので頂点0を開始頂点にします．\n");
        startnode = 0;
    } else if (argc == 2) {
        startnode = atoi(argv[1]);
        if (startnode < 0 || startnode >= N) {
            printf("不正な頂点指定だったので終了します．\n");
            return -1;
        }
    }

	dfs(startnode); // 開始頂点番号を引数にしてdfs関数を呼び出す
	return 0;
}