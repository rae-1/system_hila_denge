#include<iostream>
#include<string>
#include<chrono>
#include<thread>
#include<vector>
#include<functional>
#include<algorithm>
#include<fstream>
using namespace std;

const int N = 4e6;
string dna_seq[4][N];
string complete_dna_seq[4*N];
char seq[] = {'A', 'C', 'G', 'T'};

/*
    This function generates the DNA sequences in a recursive manner.
    The next sequence can end with either of the 4 alphabets. Iterates
    over it in a sorted manner. Once, the cur_len of the sequence 
    becomes equal to max_len it backtracks and continues to generate
    the other sequences.


    Recursive tree-
                                                    "empty string"                          NOTE: if the cur_len is zero.
                            /                   /                   \                \
                           A                    C                    G                T
                    /   /   \   \         /   /   \   \
                   AA  AC   AG   AT     CA   CC   CG   CT   ......................... and so on.


    Args:
        cur_len:    keeps track of the current length of the seq.
        max_len:    user input.
        cur_seq:    currently generated seq.
        seq_number:  
        dna_seq:    stores all the generated sequences.
*/
void generate_seq(int cur_len, int max_len, string &cur_seq, int &seq_number, int row)
{
    if (cur_len >= max_len){
        return;
    }

    for (int i = 0; i < 4; i++){
        cur_seq.push_back(seq[i]);
        // cout << cur_seq << " " << seq_number << endl;
        dna_seq[row][seq_number] = cur_seq; seq_number++;
        generate_seq(cur_len + 1, max_len, cur_seq, seq_number, row);
        cur_seq.pop_back();
    }
}

void generate_thread(int base_index, int &seq_number, int &n){
    // Fills the cur_seq with either of the options in seq array.(lenght=1)
    string cur_seq(1, seq[base_index]);
    generate_seq(1, n, cur_seq, seq_number, base_index);
}

int main(){
    int n = 1;
    scanf("%d", &n);
    
    auto start = chrono::high_resolution_clock::now();

    // Start of the initial sequences, lenght 1.
    // All four of these are independent and thus can be handed over to 4 thread.
    dna_seq[0][0] = "A", dna_seq[1][0] = "C", dna_seq[2][0] = "G", dna_seq[3][0] = "T";
    // seq_number keeps track of the index where the new generated sequence would be stored in dna_seq array.
    int seq_number[4] = {1, 1, 1, 1};


    // Spawning the threads
    vector<thread> threads;
    for (int i = 0; i < 4; i++){
        threads.emplace_back(generate_thread, i, ref(seq_number[i]), ref(n));
    }
    
    // Waiting for all the threads to complete the task
    for (thread &t : threads){
        t.join();
    }

    // Writing to a text file
    int len = seq_number[0];
    ofstream log_file("sequence.txt");
    if (log_file.is_open()){
        for (int i = 0; i < 4; i++){
            for (int j = 0; j < len; j++){
                log_file << dna_seq[i][j] << endl;
            }
        }
        log_file.close();
    }

    // Execution time
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " seconds" << endl;
}