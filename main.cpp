#include <iostream>
#include <vector>
#include <string>
#include <cmath>

struct Coordinate{
    int row; 
    int column;
    Coordinate(int row, int column){
        this->row = row;
        this->column = column;
    }
};

int size;
int unit_block_size;
std::vector<std::vector<int>> field;
bool is_answer_found = false;
void input(); void solve(); void give_answer(); void print(std::string);

int main(){
    input();
    solve();
    if(!is_answer_found) print("解が存在しません。");
}

void print(std::string s){
    std::cout << s << std::endl;
}

int int_sqrt(int n){
    return std::floor(std::sqrt(n));
}

void input(){
    print("このプログラムは数独ソルバーです。");
    print("詳しくは url のスライドを参照してください。");
    print("数独のサイズ(n × n の数独だったら n)を入力してください。");
    std::cin >> size;
    unit_block_size = int_sqrt(size);
    field.resize(size, std::vector<int>(size));
    print("数独を入力して下さい。(入力の方法はスライドを参照してください。)");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            std::cin >> field[i][j];
        }
    }
    print("入力を完了しました。");
}

Coordinate find_empty_square(){
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(field[i][j] == 0){
                return Coordinate(i, j);
            }
        }
    }
    return Coordinate(-1, -1);
}

void check_available_numbers(std::vector<bool>& available_numbers,Coordinate& square){
    int row = square.row;
    int column = square.column;
    int current_value;
    for(int i = 0; i < size; i++){
        if((current_value = field[i][column]) != 0) available_numbers[current_value] = false;
        if((current_value = field[row][i]) != 0) available_numbers[current_value] = false;
    }
    int unit_block_top_row = (row / unit_block_size) * unit_block_size;
    int unit_block_left_column = (column / unit_block_size) * unit_block_size;
    for(int i = 0; i < unit_block_size; i++){
        for(int j = 0; j < unit_block_size; j++){
            if((current_value = field[unit_block_top_row + i][unit_block_left_column + j]) != 0) available_numbers[current_value] = false;
        }
    }
}
void solve(){
    Coordinate empty_square = find_empty_square();
    if(empty_square.row == -1){
        give_answer();
        return;
    }
    std::vector<bool> available_numbers(size + 1, true);
    check_available_numbers(available_numbers, empty_square);
    int row = empty_square.row;
    int column = empty_square.column;
    for(int i = 1; i <= size; i++){
        if(available_numbers[i]){
            field[row][column] = i;
            solve();
        } 
    }
    field[row][column] = 0;
    return;
}

void give_answer(){
    if(is_answer_found){
        print("この数独は複数の解を持っています。");
        print("上の解はその一例です。");
        exit(0);
    }
    print("");
    for(const auto& row : field){
        for(const auto& value : row){
            std::cout << value << " ";
        }
        std::cout << std::endl;
    }
    is_answer_found = true;
}


/*ideas
available_numbersはCoordinateにつけるとどうだろう。z
*/
