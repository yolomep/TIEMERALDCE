#include <iostream>
#include <bits/stdc++.h>
using namespace std;
//This is the type checking function
double typ1(int m, int t){
    int32_t i = 18 * m + t;
    int w = i % 3 * 2;
    //32 is there to make text look "normal"
    cout << "J:2JJJ;YQJV>N:;ZIJJ5&ZJZ*[Y;KJVF;KZJ6I6YN>HJNJNFJZ:EYZJ:[UZIJ^J7JI:]9=JIZBJ>IINK:JFBZN:U:KJJ:JJ+FJNJN6NI:IJO"[i / 3] - 32;
    //*→↕***1*6▲.→)**§♠:*:\n;9&*▬)▬9.▲(*.*.&*:→%9:*→;5:)*>*↨*)→=↓↔*):\"*▲)).+→*&\":.→5→+**→**\v&*.*.▬.)→)*/
    cout << endl << w << endl;
    cout << i << endl;
    cout << (("J:2JJJ;YQJV>N:;ZIJJ5&ZJZ*[Y;KJVF;KZJ6I6YN>HJNJNFJZ:EYZJ:[UZIJ^J7JI:]9=JIZBJ>IINK:JFBZN:U:KJJ:JJ+FJNJN6NI:IJO"[i / 3] - 32) >> 0) << endl;
    i = ("J:2JJJ;YQJV>N:;ZIJJ5&ZJZ*[Y;KJVF;KZJ6I6YN>HJNJNFJZ:EYZJ:[UZIJ^J7JI:]9=JIZBJ>IINK:JFBZN:U:KJJ:JJ+FJNJN6NI:IJO"[i / 3] - 32) >> i % 3 * 2 & 3;
    //8 bits into 
    cout << (i & 3) << endl;
    cout << (i + i/3);
    return (i + i/3)/2.; //genius! turns i = 1, 2, 3 into 0.5, 1, 2
}

double type(int m, int t){
    int32_t i = 18 * m + t;
    i = ("UZJZ9N7JZJ;J=JV9;FJJJJAF>F*K:JU:ZKZFJ[F5C]ZJ6JEC;NN8KNZFKZIFJJOFJ&YJEMFUKZ9[JFJHJNN:JJJJZDIJGJZVEVJJKGJJINN9"[i / 3] - 32) >> i % 3 * 2 & 3;
    return (i + i/3)/2.;
}

// std::ostream& writeString(std::ostream& out, std::string const& s)
// {
//    for ( auto ch : s )
//    {
//       switch (ch)
//       {
//          case '\'':
//             out << "\\'";
//             break;

//          case '\"':
//             out << "\\\"";
//             break;

//          case '\?':
//             out << "\\?";
//             break;

//          case '\\':
//             out << "\\\\";
//             break;

//          case '\a':
//             out << "\\a";
//             break;

//          case '\b':
//             out << "\\b";
//             break;

//          case '\f':
//             out << "\\f";
//             break;

//          case '\n':
//             out << "\\n";
//             break;

//          case '\r':
//             out << "\\r";
//             break;

//          case '\t':
//             out << "\\t";
//             break;

//          case '\v':
//             out << "\\v";
//             break;

//          default:
//             out << ch;
//       }
//    }

//    return out;
// }

// void swapRow(int grid[][18], int a, int b){
//     for (int i = 0; i < 18; ++i) {
//         swap(grid[a][i], grid[b][i]);
//     }
// }

// void swapColumn(int grid[][18], int a, int b){
//     for (int i = 0; i < 18; ++i) {
//         swap(grid[i][a], grid[i][b]);
//     }
// }

// void swapG(int grid[][18], int a, int b){
//     swapRow(grid, a, b);
//     swapColumn(grid, a, b);
// }

// int indexOf(string arr[], string find) {
//     int i = 0;
//     while (i < 18) {
//         if (arr[i] == find) {
//             break;
//         }
//         i++;
//     }
//     return i;
// }

// void sortG(int grid[][18], string unsorted[], string sorted[]) {
//     int toSort[18];
//     for(int i = 0; i < 18; i++){
//         toSort[i] = indexOf(sorted, unsorted[i]);
//     }
//     int N = 18;
//     int i, j;
 
//     for (i = 1; i < N; i++) {
//         j = i;
 
//         // Insert V[i] into list 0..i-1
//         while (j > 0 && toSort[j] < toSort[j - 1]) {
 
//             // Swap V[j] and V[j-1]
//             swap(toSort[j], toSort[j - 1]);
//             swapG(grid, j, j - 1);
//             // Decrement j by 1
//             j -= 1;
//         }
//     }
// }


string transform(int grid[][18]) {
    string ret = "";
    int w = 0;
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 18; j += 3){
            w++;
            char c = '\0';
            // c += grid[i][j];
            // c <<= 2;
            // c += grid[i][j + 1];
            // c <<= 2;
            // c += grid[i][j + 2];
            for(int k = 2; k >= 0; k--){
                
                c += grid[i][j + k];
                if(k != 0)
                    c <<= 2;
                //cout << (int) c << endl;
            }
            //cout << c << endl;
            
            ret += (c + 32);
        }
    }
    //cout << w;
    return ret;
}
//NorFigFlyPoiGroRocBugGhoSteFirWatGraElePsyIceDraDarFai
//nor is 0
int main() {
    cout << type(1, 0) << endl << type(1, 1) << endl;
    // for(int i = 0; i < 5; i++){
    //     cout << type(i , i) << endl;
    // }
    return 0;
    string input = R"(113223222223121232
311222223222321222
131222213121321212
222222222222102212
231212220322221222
113221223322223212
222323212111302133
223222211222112302
321232232021322232
223212322223122212
222222332212222210
123222112132212113
322223121323222212
222022222232232221
222222222222223012
122222312222223213
112213222222322312
222222122232232121)";
    stringstream input_stringstream(input);
    int grid[18][18];
    for(int i = 0; i < 18; i++){
        string line;
        getline(input_stringstream, line);
        for(int j = 0; j < 18; j++) {
            grid[i][j] = line[j] - '0';
        }
    }

//     swapColumn(grid, 1, 2);
//     swapRow(grid, 1, 2);
//     cout << endl;

//     string unsort[] = {"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass",
// "Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"};
//     string sorted[] = {"Fire", "Water", "Grass", "Normal", "Electric", "Ice", "Fighting", "Poison", "Ground", "Flying", "Psychic", 
// "Bug", "Rock", "Ghost", "Dragon", "Fairy", "Steel", "Dark"};
    //transform(grid);
    cout << transform(grid) << endl;
    // sortG(grid, unsort, sorted);
    // for(int i = 0; i < 18; i++) {
    //     for(int j = 0; j < 18; j++){
    //         cout << grid[i][j];
    //     }
    //     cout << endl;
    // }
    // cout << transform(grid);
//     // int i = 0;
//     // i += 2;
//     // i <<= 2;
//     // i += 2;
//     // i <<= 2;
//     // i += 2;
//     // cout << i;
//     // cout << (char) i;
}
/*
J:2JJJ
;YQJV>
N:;ZIJ
J5&ZJZ
*[Y;KJ
VF;KZJ
6I6YN>
HJNJNF
JZ:EYZ
J:[UZI
J^J7JI
:]9=JI
ZBJ>II
NK:JFB
ZN:U:K
JJ:JJ+
FJNJN6
NI:IJO
*/
/*
"Fire", "Water", "Grass", "Normal", "Electric", "Ice", "Fighting", "Poison", "Ground", "Flying", "Psychic", 
"Bug", "Rock", "Ghost", "Dragon", "Fairy", "Steel", "Dark"
J:2JJJ;YQJV>N:;ZIJ
J5&ZJZ*[Y;KJVF;KZJ
6I6YN>HJNJNFJZ:EYZ
J:[UZIJ^J7JI:]9=JI
ZBJ>IINK:JFBZN:U:K
JJ:JJ+FJNJN6NI:IJO
NorFigFlyPoiGroRocBugGhoSteFirWatGraElePsyIceDraDarFai
   Normal   222221201222222222
   Fighting 421124104222214241
A  Flying   242221421224122222
t  Poison   222111210224222224
t  Ground   220424124421422222
a  Rock     214212421422224222
c  Bug      211122211124242241
k  Ghost    022222242222242212
i  Steel    222224221112124224
n  Fire     222221424114224122
g  Water    222244222411222122
   Grass    221144121141222122
T  Electric 224202222241122122
y  Psychic  242422221222212202
p  Ice      224242221114221422
e  Dragon   222222221222222420
   Dark     212222242222242211
   Fairy    242122221122222442

index begin on 0 
"Normal", "Fighting", "Flying", "Poison", "Ground", "Rock", "Bug", "Ghost", "Steel", "Fire", "Water", "Grass",
"Electric", "Psychic", "Ice", "Dragon", "Dark", "Fairy"
1 Fir
2 Wtr
3 Grs
4 Nrm
5 Elc
6 Ice
7 Ftg
8 Psn
9 Grd
10 Fly
11 Psy
12 Bug
13 Roc
14 Gho
15 Drg
16 Far
17 Stl
18 Dar
"Fire", "Water", "Grass", "Normal", "Electric", "Ice", "Fighting", "Poison", "Ground", "Flying", "Psychic", 
"Bug", "Rock", "Ghost", "Dragon", "Fairy", "Steel", "Dark"
113223222223121232
311222223222321222
131222213121321212
222222222222102212
231212220322221222
113221223322223212
222323212111302133
223222211222112302
321232232021322232
223212322223122212
222222332212222210
123222112132212113
322223121323222212
222022222232232221
222222222222223012
122222312222223213
112213222222322312
222222122232232121



220424124421422222
214212421422224222
211122211124242241
022222242222242212
222224221112124224
222221424114224122
222244222411222122
221144121141222122
224202222241122122
242422221222212202
224242221114221422
222222221222222420
212222242222242211
242122221122222442



222221201222222222
421124104222214241
242221421224122222
222111210224222224
220424124421422222
214212421422224222
211122211124242241
022222242222242212
222224221112124224
222221424114224122
222244222411222122
221144121141222122
224202222241122122
242422221222212202
224242221114221422
222222221222222420
212222242222242211
242122221122222442












222221201222222222
321123103222213231
232221321223122222
222111210223222223
220323123321322222
213212321322223222
211122211123232231
022222232222232212
222223221112123223
222221323113223122
222233222311222122
221133121131222122
223202222231122122
232322221222212202
223232221113221322
222222221222222320
212222232222232211
232122221122222332

222221201222222222
232221321223122222
321123103222213231
222111210223222223
220323123321322222
213212321322223222
211122211123232231
022222232222232212
222223221112123223
222221323113223122
222233222311222122
221133121131222122
223202222231122122
232322221222212202
223232221113221322
222222221222222320
212222232222232211
232122221122222332
*/