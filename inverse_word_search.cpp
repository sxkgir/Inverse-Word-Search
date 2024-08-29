#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>
bool fillInBlank(std::set<std::vector<std::vector<char>>>& solution, std::vector<std::vector<char>>& board, std::vector<std::string>& dont_appear);

void displayBoard(const std::vector<std::vector<char>>& board) {
    for (const std::vector<char>& row : board) {
        for (char cell : row) {
            std::cout << cell;
        }
        std::cout << std::endl;
    }
    std::cout << '\n';
}
void outputBoard(const std::set<std::vector<std::vector<char>>>& solutionSets, std::ofstream& output, const std::string& solutionType) {
    //this function includes the flipped vertical and is included in the solutionSets

    if (solutionType == "one_solution") {
        if (!solutionSets.empty()) {
            const std::vector<std::vector<char>>& firstSolution = *(solutionSets.begin());
            output << "Board:" << '\n';
            for (size_t y = 0; y < firstSolution.size(); ++y) {
                for (size_t x = 0; x < firstSolution[y].size(); ++x) {
                    output << firstSolution[y][x];
                }
                output << '\n';
            }
        }
        return;
    }

    // Output each solution set to the file
    output << solutionSets.size() << " solution(s)" << std::endl;
    for (const std::vector<std::vector<char>>& solution : solutionSets) {
        int height = solution.size();
        int width = solution[0].size();
        output << "Board:" << '\n';
        for (size_t y = 0; y < height; y++) {
            for (size_t x = 0; x < width; x++) {
                output << solution[y][x];
            }
            output << '\n';
        }

    }
}
 
void parsefile(std::vector<std::string>& appear,std::vector<std::string>& dont_appear,std::ifstream& puzzle, int& height, int& width){
    puzzle >> width >> height;
    std::string operation;
    while (puzzle >> operation) {
    if (operation == "+") {
        // Read and store the word
        std::string word;
        puzzle >> word;
        appear.push_back(word);
    } else if (operation == "-") {
        // Read and discard the word
        std::string word;
        puzzle >> word;
        dont_appear.push_back(word);

    }
    }   
}


bool horizontal(std::string word,std::vector<std::vector<char>>&board,int x,int y){
    // checks if the current x position + the word lenghth is less than the row

    if (x+word.length() > board[0].size()){
        return false;
    }

    std::vector<std::vector<char>> board1  = board;
    for (int i = 0; i < word.length(); i++){
        //if it is not equal to '.' and is not equal to a letter of the word if there is a letter at anypoint it will return false
        if (board1[y][x+i] != '.' && board1[y][x + i] != word[i]){
            return false;
        }
    }
    for (int i = 0; i < word.length(); i++){
            // if it still hasnt returned false then you can safely add the words
            board1[y][x+i] = word[i];
    }

    // Assign the modified board back to the original board
    board = board1;


    return true;

}

// same logic as the horizontal but backwards
bool horizontal_backward(const std::string& word, std::vector<std::vector<char>>& board, int x, int y) {
    //current x position minus word length should be less than -1 since is at position 2 in the graph and word length is 3
    // 2 - 3 = -1 but it can fit so -1 < -1 is false and thus will not return false
    if (x - word.length() < -1) {
        return false;  // Word too long to fit horizontally backward
    }

    for (int i = 0; i < word.length(); i++) {
        if (board[y][x - i] != '.' && board[y][x - i] != word[i]) {
            return false;  // Conflict with existing letter
        }
    }

    for (int i = 0; i < word.length(); i++) {
        board[y][x - i] = word[i];
    }

    return true;
}

//same logic as the other direction but different axis
bool vertical(const std::string& word, std::vector<std::vector<char>>& board, int x, int y) {
    if (y + word.length() > board.size()) {
        return false;  // Word too long to fit vertically
    }

    for (int i = 0; i < word.length(); i++) {
        if (board[y + i][x] != '.' && board[y + i][x] != word[i]) {
            return false;  // Conflict with existing letter
        }
    }

    for (int i = 0; i < word.length(); i++) {
        board[y + i][x] = word[i];
    }

    return true;
}

bool vertical_backward(const std::string& word, std::vector<std::vector<char>>& board, int x, int y) {
    if (y - word.length() < -1) {
        return false;  // Word too long to fit vertically backward
    }

    for (int i = 0; i < word.length(); i++) {
        if (board[y - i][x] != '.' && board[y - i][x] != word[i]) {
            return false;  // Conflict with existing letter
        }
    }

    for (int i = 0; i < word.length(); i++) {
        board[y - i][x] = word[i];
    }

    return true;
}

bool diagonal_top_left_corner(const std::string& word, std::vector<std::vector<char>>& board, int x, int y) {
    if (x + word.length() > board[0].size() || y + word.length() > board.size()) {
        return false;  // Word too long to fit diagonally
    }

    for (int i = 0; i < word.length(); i++) {
        if (board[y + i][x + i] != '.' && board[y + i][x + i] != word[i]) {
            return false;  // Conflict with existing letter
        }
    }

    for (int i = 0; i < word.length(); i++) {
        board[y + i][x + i] = word[i];
    }

    return true;
}

bool diagonal_top_left_corner_backward(const std::string& word, std::vector<std::vector<char>>& board, int x, int y) {
    if (x - word.length() < -1 || y - word.length() < -1) {
        return false;  // Word too long to fit diagonally backward
    }

    for (int i = 0; i < word.length(); i++) {
        if (board[y - i][x - i] != '.' && board[y - i][x - i] != word[i]) {
            return false;  // Conflict with existing letter
        }
    }

    for (int i = 0; i < word.length(); i++) {
        board[y - i][x - i] = word[i];
    }

    return true;
}

bool diagonal_top_right_corner(const std::string& word, std::vector<std::vector<char>>& board, int x, int y) {
    if (x - word.length() < -1 || y + word.length() > board.size()) {
        return false;  // Word too long to fit diagonally from top-right corner
    }

    for (int i = 0; i < word.length(); i++) {
        if (board[y + i][x - i] != '.' && board[y + i][x - i] != word[i]) {
            return false;  // Conflict with existing letter
        }
    }

    for (int i = 0; i < word.length(); i++) {
        board[y + i][x - i] = word[i];
    }

    return true;
}

bool diagonal_top_right_corner_backward(const std::string& word, std::vector<std::vector<char>>& board, int x, int y) {
    if (x + word.length() > board[0].size() || y - word.length() < -1) {
        return false;  // Word too long to fit diagonally backward from top-right corner
    }

    for (int i = 0; i < word.length(); i++) {
        if (board[y - i][x + i] != '.' && board[y - i][x + i] != word[i]) {
            return false;  // Conflict with existing letter
        }
    }

    for (int i = 0; i < word.length(); i++) {
        board[y - i][x + i] = word[i];
    }

    return true;
}



bool checkWordsDontAppear(const std::vector<std::vector<char>>& board, const std::vector<std::string>& dont_appear) {
    // Convert the vector of words to a set for faster lookup
    if (dont_appear.size() == 0){
        return true;

    }

    std::set<std::string> dontAppearSet(dont_appear.begin(), dont_appear.end());

    int height = board.size();
    int width = board[0].size();

    // Check horizontally
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::string word;
            // Right
            for (int k = j; k < width; ++k) {
                word += board[i][k];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
            word.clear();
            // Left
            for (int k = j; k >= 0; --k) {
                word += board[i][k];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
        }
    }

    // Check vertically
    for (int j = 0; j < width; ++j) {
        for (int i = 0; i < height; ++i) {
            std::string word;
            // Down
            for (int k = i; k < height; ++k) {
                word += board[k][j];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
            word.clear();
            // Up
            for (int k = i; k >= 0; --k) {
                word += board[k][j];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
        }
    }

    // Check diagonally (top-left to bottom-right)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::string word;
            // Bottom-right
            for (int k = 0; i + k < height && j + k < width; ++k) {
                word += board[i + k][j + k];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
            word.clear();
            // Top-left
            for (int k = 0; i - k >= 0 && j - k >= 0; ++k) {
                word += board[i - k][j - k];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
        }
    }

    // Check diagonally (top-right to bottom-left)
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            std::string word;
            // Bottom-left
            for (int k = 0; i + k < height && j - k >= 0; ++k) {
                word += board[i + k][j - k];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
            word.clear();
            // Top-right
            for (int k = 0; i - k >= 0 && j + k < width; ++k) {
                word += board[i - k][j + k];
                if (dontAppearSet.find(word) != dontAppearSet.end()) {
                    return false; // Word found in don't appear list
                }
            }
        }
    }

    // If none of the words from the don't appear list are found, return true
    return true;
}




bool insert_words_optimized(std::set<std::vector<std::vector<char>>>& solution, std::vector<std::vector<char>>& board, std::vector<std::string>& dont_appear, std::vector<std::string>& words, int index) {
    if (index >= words.size()) {
        // If we've placed all words, check for "don't appear" words
        if (checkWordsDontAppear(board, dont_appear)) {
            solution.insert(board);
            return true; // Solution found
        }
        return false; // Continue searching
    }

    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[0].size(); x++) {
            std::vector<std::vector<char>> originalBoard = board; // Preserve board state for backtracking

            // Attempt to place the current word in all directions from this point
            if (horizontal(words[index], board, x, y) || 
                vertical(words[index], board, x, y) ||
                horizontal_backward(words[index], board, x, y) ||
                vertical_backward(words[index], board, x, y) ||
                diagonal_top_left_corner(words[index], board, x, y) ||
                diagonal_top_right_corner(words[index], board, x, y) ||
                diagonal_top_left_corner_backward(words[index], board, x, y) ||
                diagonal_top_right_corner_backward(words[index], board, x, y)) {
                
                if (insert_words_optimized(solution, board, dont_appear, words, index + 1)) {
                    return true; // Success path found
                }
                board = originalBoard; // Backtrack: Restore board state
            }
        }
    }

    return false; // No valid placement found for this word
}




bool fillInBlank(std::set<std::vector<std::vector<char>>>& solution, std::vector<std::vector<char>>& board, std::vector<std::string>& dont_appear) {
    // Check if the board is completely filled
    bool filled = true;
    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[0].size(); x++) {
            if (board[y][x] == '.') {
                filled = false;
                break;
            }
        }
        if (!filled) break; // If any cell is empty, the board is not filled
    }

    // If the board is filled and words don't appear, return true
    if (filled && checkWordsDontAppear(board, dont_appear)) {
        solution.insert(board);
        return true;
    }

    // Iterate over each cell in the board
    for (int y = 0; y < board.size(); y++) {
        for (int x = 0; x < board[0].size(); x++) {
            // If the cell is empty, try filling it with each letter from 'a' to 'z'
            if (board[y][x] == '.') {
                for (char letter = 'a'; letter <= 'z'; letter++) {
                    // Try placing the letter in the cell
                    board[y][x] = letter;

                    fillInBlank(solution, board, dont_appear);
                    // Backtrack: Reset the cell to its original empty state before trying the next letter at the end of the last backtrack so when it reaches its original case or the case before
                    // the board will not be filled
                    board[y][x] = '.';
                }
                return false;
            }
            
        }
    }

    // If no solution is found, return false
    return false;
}

void flipVertical(std::set<std::vector<std::vector<char>>>& solutionSets){
    for (const std::vector<std::vector<char>>& solution : solutionSets){
        std::vector<std::vector<char>> temp;
        int height = solution.size();
        int width = solution[0].size();
        for (int y = 0; y < height; y++){
            std::vector<char> row;
            for (int x = 0; x < width;x++){
                row.push_back(solution[height-1-y][x]);
            }
            temp.push_back(row);
        }
        solutionSets.insert(temp);
    }
    
}

void flipHorizontal(std::set<std::vector<std::vector<char>>>& solutionSets){
    for (const std::vector<std::vector<char>>& solution : solutionSets){
        std::vector<std::vector<char>> temp;
        int height = solution.size();
        int width = solution[0].size();
        for(int y = 0; y < height;y++){
            std::vector<char> row;
            for(int x = 0; x < width;x++){
                row.push_back(solution[y][width-x-1]);
            }
            temp.push_back(row);
        }
        solutionSets.insert(temp);

    }
}



bool compareStringSize(const std::string& a, const std::string& b) {
    return a.size() > b.size(); // Compare based on string length in descending order
}

int main(int argc, char* argv[]) {
    std::string puzzle_file_name = argv[1];
    std::string output_file_name = argv[2];
    std::string one_or_all_soultion = argv[3];

    std::ifstream puzzle(puzzle_file_name);
    if(!puzzle.is_open()){
        std::cerr << "could not open puzzle file";
    }

    std::ofstream output(output_file_name);

    if(!output.is_open()){
        std::cerr << "could not open output" << std::endl;
    }


    std::vector<std::string> appear;
    std::vector<std::string> dont_appear;

    int height;
    int width;

    parsefile(appear,dont_appear,puzzle,height,width);



    std::vector<std::vector<char>> board;

    for(int y = 0; y < height; y++){
        std::vector<char> row; // Create a new row vector for each y
        for(int x = 0; x < width; x++){
            row.push_back('.'); // Add 'a' to each element of the row
        }
        board.push_back(row); // Add the row to the board
    }


    // maybe you can just print the flipped grids of the original
    std::set<std::vector<std::vector<char>>> solutionSets;
    
    std::sort(appear.begin(),appear.end(),compareStringSize);
    for (auto word : appear){
        std::cout << word << std::endl;
    }
    insert_words_optimized(solutionSets,board,dont_appear,appear,0);
    flipVertical(solutionSets);
    flipHorizontal(solutionSets);
    outputBoard(solutionSets,output,one_or_all_soultion);

    return 0;

}