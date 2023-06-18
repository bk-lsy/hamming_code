#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

const int IN_N = 3;
const int OUT_N = 3;

struct Hamming {
    int h[3][7] = { 0 };
    int g[4][7] = { 0 };
    int s[3] = { 0 };
};

void hamToinfor(int ham_s[OUT_N][7],Hamming info) {

    int infor_out[OUT_N][4];
    int s_out[OUT_N][3];
    for (int k = 0; k < OUT_N; k++) {
        for (int i = 0; i < 4; i++) {
            infor_out[k][i]=ham_s[k][i];
        }
    }


    for (int k = 0; k < OUT_N; k++) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                s_out[k][i] += info.h[i][j] * ham_s[k][j];
            }
            s_out[k][i] = (s_out[k][i]+2)%2;
        }
    }
    for (int k = 0; k < OUT_N; k++) {
        int check = 0;
        for (int i = 0; i < 3; i++) {
            check += (s_out[k][i] != info.s[i]);
        }
        if (check == 2) {
            for (int i = 0; i < 3; i++) {
                if (s_out[k][i] == info.s[i]) {
                    infor_out[k][i] = abs(infor_out[k][i] - 1);
                }
            }
        }
        if (check == 3){
            infor_out[k][3] = abs(infor_out[k][3] - 1);
        }
   }
    cout << "译码结果:" << endl;
    for (int k = 0; k < OUT_N; k++) {
        for (int i = 0; i < 4; i++) {
            cout << infor_out[k][i];
        }
        cout << endl;
    }
}

void inforToham(int infor_s[IN_N][4], Hamming info)
{
    int ham_out[IN_N][7] = { 0 };
    for (int k = 0; k < IN_N; k++) {
        for (int i = 0; i < 7; i++) {      
            for (int j = 0; j < 4; j++) {
                ham_out[k][i] += infor_s[k][j] * info.g[j][i];
            }
            ham_out[k][i] = (ham_out[k][i] + 2) % 2;
        }
    }
    cout << "编码结果:" << endl;
    for (int i = 0; i < IN_N; i++) {
        for (int k = 0; k < 7; k++) {
            cout << ham_out[i][k] ;
        }
        cout << endl;
   }
}

int main() {

    Hamming info;

    cout << "请输入监督矩阵" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 7; j++) {
            cin >> info.h[i][j];
        }
    }
    cout << "请输入生成矩阵" << endl;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 7; j++) {
            cin >> info.g[i][j];
        }
    }


    cout << "请输入校验表" << endl;
    for (int i = 0; i < 3; i++) {
        cin >> info.s[i];
    }
    cout << "请输入" << IN_N << "组信息码元" << endl;
    int infor_s[IN_N][4];
    for (int k = 0; k < IN_N; k++) {
        for (int j = 0; j < 4; j++) {
            char c = 0;
            cin >> c;
            infor_s[k][j] = c - '0';
        }
    }
    inforToham(infor_s, info);


    cout << "请输入" << OUT_N << "组汉明码字" << endl;


    int ham_s[OUT_N][7];

    for (int k = 0; k < OUT_N; k++) {
        for (int j = 0; j < 7; j++) {
            char c = 0;
            cin >> c;
            ham_s[k][j] = c - '0';
        }
    }
    hamToinfor(ham_s, info);


    return 0;
}


/*
测试数据
0 1 1 1 1 0 0
1 0 1 1 0 1 0
1 1 0 1 0 0 1

1 0 0 0 0 1 1
0 1 0 0 1 0 1
0 0 1 0 1 1 0
0 0 0 1 1 1 1
0 0 0
0110
1001
0010
0101
0110011
1001100
0010110
0101010


0 1 1 1 1 0 0
1 0 1 1 0 1 0
1 1 0 1 0 0 1
1 0 0 0 0 1 1
0 1 0 0 1 0 1
0 0 1 0 1 1 0
0 0 0 1 1 1 1
0 0 0
0110 1001 0010
0110011 0111011 0000011


1 1 1 0 1 0 0
1 1 0 1 0 1 0
1 0 1 1 0 0 1
1 0 0 0 1 1 1
0 1 0 0 1 1 0
0 0 1 0 1 0 1
0 0 0 1 0 1 1
0 0 0
0110 1001 0010
0110011 0111011 0000011



*/