    #include <iostream>
    #include <vector>
    #include <fstream>
    #include <string>
    #include <algorithm>
    #include <set>

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


    void displayBoard(std::vector<std::vector<char>>& board){
        for(int y = 0; y < board.size(); y++){
            for (int x = 0; x < board[0].size(); x++){
                std::cout << board[y][x] << "  ";
            }
            std::cout << '\n';
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




    void insert_words(std::set<std::vector<std::vector<char>>>& solution,std::vector<std::vector<char>>& board,std::vector<std::string>& dont_appear,std::vector<std::string>& words, int width, int height, int index){
        std::vector<std::vector<char>> board1  = board;


        if (index >= words.size()) {
            if (checkWordsDontAppear(board,dont_appear)){
                solution.insert(board);
            }
            return;
        }

            
            //loops through every posiiton to see if it can fit even in the first case when it is backtracing
            for (int y = 0;y < height; y++){

            for (int x = 0; x < width; x++){
            
        //if one word cannot fit into any of the cases then it wont even recurse 

        if (horizontal(words[index], board1, x,y)){


                // Reset x if it exceeds the width
                insert_words(solution,board1,dont_appear, words, width, height, index+1); 

            }
            //goes back to the original state before any word is inserted tot see if it can inserted another
            board1 = board;

            if (horizontal_backward(words[index], board1, x,y)){
                insert_words(solution,board1,dont_appear, words, width, height, index+1);
            }


            board1 = board; 

            if (vertical(words[index], board1, x, y)){
                insert_words(solution,board1,dont_appear, words, width, height, index+1);
                

                }

            board1 = board; 

            if (vertical_backward(words[index], board1, x, y)){

                insert_words(solution,board1,dont_appear, words, width, height, index+1);
            }

            

            board1 = board;

            if (diagonal_top_left_corner(words[index], board1, x,y)){

                insert_words(solution,board1,dont_appear, words, width, height, index+1);

            }

            board1 = board;

            if (diagonal_top_left_corner_backward(words[index], board1, x,y)){

                insert_words(solution,board1,dont_appear, words, width, height, index+1);

            }
            board1 = board;

            if(diagonal_top_right_corner(words[index], board1, x,y)){

                insert_words(solution,board1,dont_appear, words, width, height, index+1);

            }

            board1 = board;

            if (diagonal_top_right_corner_backward(words[index], board1, x,y)){
                insert_words(solution,board1,dont_appear, words, width, height, index+1);

            }
            board1 = board;

                }

            }
        }

void outputBoard(const std::set<std::vector<std::vector<char>>>& solutionSets, std::ofstream& output, const std::string& solutionType) {
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
        output << "Board:" << '\n';
        for (size_t y = 0; y < solution.size(); ++y) {
            for (size_t x = 0; x < solution[y].size(); ++x) {
                output << solution[y][x];
            }
            output << '\n';
        }
    }
}

    std::vector<std::vector<std::string>> createStartingWordVariations(const std::vector<std::string>& originalVector) {
        std::vector<std::vector<std::string>> variations;

        for (size_t i = 0; i < originalVector.size(); ++i) {
            std::vector<std::string> variation;
            for (size_t j = i; j < originalVector.size(); ++j) {
                variation.push_back(originalVector[j]);
            }
            for (size_t j = 0; j < i; ++j) {
                variation.push_back(originalVector[j]);
            }
            variations.push_back(variation);
        }

        return variations;
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

        std::vector<std::vector<std::string>> differentStart;



        std::vector<std::vector<char>> board;

        for(int y = 0; y < height; y++){
            std::vector<char> row; // Create a new row vector for each y
            for(int x = 0; x < width; x++){
                row.push_back('.'); // Add 'a' to each element of the row
            }
            board.push_back(row); // Add the row to the board
        }

        differentStart = createStartingWordVariations(appear);

        // maybe you can just print the flipped grids of the original
        std::set<std::vector<std::vector<char>>> solutionSets;

        for (int i = 0; i < differentStart.size(); i++){
            insert_words(solutionSets,board,dont_appear,differentStart[i],width,height,0);
            
        }


        outputBoard(solutionSets,output,one_or_all_soultion);

        return 0;
    }