/**
 * @file cnfsat2002.cpp
 * @brief CNF (Conjunctive Normal Form) SAT formula validator
 * @author K Vikashh Adaikalavan
 * @date 2025
 * 
 * This program reads CNF formulas from a file and validates them by checking
 * if clauses are valid. A clause is considered valid if it contains
 * both a literal and its negation (making it always true).
 */

#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
#include<unordered_set>
#include <vector>
#include <chrono>

#include "include/parser/fx_parser.h"
#include "include/utils/converters.h"
#include "include/utils/utils.h"

using namespace std;
using namespace std::chrono;

/**
 * @brief Counts the number of valid clauses in a CNF formula file
 * 
 * A clause is considered valid if it contains both a literal and its negation
 * (e.g., x and -x), which makes the clause always satisfiable (tautology).
 * 
 * @param filepath Path to the CNF file in DIMACS format
 * @return int Number of valid clauses found, or -1 if file cannot be opened
 * 
 * @note The CNF file should follow DIMACS format:
 *       - Header line: p cnf <num_variables> <num_clauses>
 *       - Each clause line contains space-separated integers ending with 0
 *       - Negative numbers represent negated literals
 * 
 * @warning This function opens and reads the file each time it's called
 */
int cnf_validcno(string filepath)
{
    int valid_clause_no = 0;
    ifstream f(filepath);

    if(!f.is_open())
    {
        cout<<"File is not opened";
        return -1;
    }

    string line;
    string token;
    
    // Skip lines until we find the problem line (starts with 'p')
    while(getline(f,line))
    {
        if(line[0] == 'p') break;
    }
    
    // Parse the problem line: p cnf <variables> <clauses>
    stringstream ss(line);
    getline(ss,token,' ');  // 'p'
    getline(ss,token,' ');  // 'cnf'
    getline(ss,token,' ');  // number of variables
    int var_no = stoi(token);
    getline(ss,token,' ');  // number of clauses
    int clause_no = stoi(token);
    int no;

    unordered_set<int> uset;
    
    // Process each clause
    for(int i = 0; i<clause_no; i++)
    {
        uset.clear();

        getline(f,line);
        stringstream ss(line);
        
        // Read each literal in the clause
        while(getline(ss,token,' '))
        {
            no = stoi(token);
            if(no==0)  // 0 marks end of clause
            {
                continue;
            }
            else
            {
                // Check if negation of current literal already exists
                if(uset.find(no*(-1))!=uset.end())
                {
                    valid_clause_no++;
                    break;  // Found a tautology, move to next clause
                }
                else
                {
                    uset.insert(no);
                }
            }
        }
    }
    f.close();

    return valid_clause_no;
}

/**
 * @brief Counts the number of non-valid (non-tautology) clauses in a CNF formula
 * 
 * Calculates the difference between total clauses and valid clauses.
 * 
 * @param filepath Path to the CNF file in DIMACS format
 * @return int Number of non-valid clauses, or -1 if file cannot be opened
 * 
 * @see cnf_validcno()
 */
int cnf_non_valid_cno(string filepath)
{
    ifstream f(filepath);

    if(!f.is_open())
    {
        cout<<"File is not opened";
        return -1;
    }

    string line;
    string token;
    
    // Skip to problem line
    while(getline(f,line))
    {
        if(line[0] == 'p') break;
    }
    
    // Parse problem line
    stringstream ss(line);
    getline(ss,token,' ');
    getline(ss,token,' ');
    getline(ss,token,' ');
    int var_no = stoi(token);
    getline(ss,token,' ');
    int clause_no = stoi(token);
    int no;
    
    return clause_no-cnf_validcno(filepath);
}

/**
 * @brief Checks if all clauses in a CNF formula are valid (tautologies)
 * 
 * A CNF formula is considered "valid" in this context if all of its clauses
 * are tautologies (each contains both a literal and its negation).
 * 
 * @param filepath Path to the CNF file in DIMACS format
 * @return bool True if all clauses are valid (tautologies), false otherwise
 * @return bool Returns false (cast from -1) if file cannot be opened
 * 
 * @note This definition of "valid" is specific to this implementation and
 *       differs from standard SAT terminology
 * 
 * @see cnf_validcno()
 */
bool cnf_validitychecker(string filepath)
{
    ifstream f(filepath);

    if(!f.is_open())
    {
        cout<<"File is not opened";
        return -1;
    }

    string line;
    string token;
    
    // Skip to problem line
    while(getline(f,line))
    {
        if(line[0] == 'p') break;
    }
    
    // Parse problem line
    stringstream ss(line);
    getline(ss,token,' ');
    getline(ss,token,' ');
    getline(ss,token,' ');
    getline(ss,token,' ');
    int clause_no = stoi(token);
    int valid_clauseno = cnf_validcno(filepath);
    f.close();
    
    if(valid_clauseno == clause_no) return true;
    else return false;
}

/**
 * Convert contents of a cnf file to a propositional logic statement(string)
 * @param filename Path to cnf file
 * @return Tuple with propositional logic statement as the first index and number of variables in the statement as second index
 */
std::pair<std::string, int> cnfToString(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        std::exit(EXIT_FAILURE);
    }

    std::vector<std::vector<int>> clauses;
    std::vector<int> currentClause;
    int n_vars = 0;

    std::string token;
    while (file >> token) {
        if (token == "c") {
            // skip rest of the comment line
            std::string rest;
            std::getline(file, rest);
            continue;
        }

        if (token == "p") {
            // header: p cnf <vars> <clauses>
            std::string format;
            int vars = 0;
            int clausesCount = 0;
            // read the next three tokens safely
            if (!(file >> format >> vars >> clausesCount)) {
                // malformed header: ignore
                continue;
            }
            if (format == "cnf") {
                n_vars = vars;
            }
            continue;
        }

        // token should be a literal (decimal integer), attempt to parse
        try {
            int lit = std::stoi(token);
            if (lit == 0) {
                if (!currentClause.empty()) {
                    clauses.push_back(std::move(currentClause));
                    currentClause.clear();
                }
            } else {
                currentClause.push_back(lit);
            }
        } catch (const std::exception& e) {
            // if a non-integer token sneaks in, skip it but warn (optional)
            std::cerr << "Warning: skipping non-integer token '" << token << "'\n";
            // continue parsing
        }
    }

    // If file ended without final 0, close the last clause
    if (!currentClause.empty()) {
        clauses.push_back(std::move(currentClause));
    }

    // Build the output string using ~ for negation
    std::ostringstream out;
    for (size_t i = 0; i < clauses.size(); ++i) {
        out << "(";
        for (size_t j = 0; j < clauses[i].size(); ++j) {
            int lit = clauses[i][j];
            if (lit < 0) {
                out << "~" << (-lit);
            } else {
                out << lit;
            }
            if (j + 1 < clauses[i].size())
                out << " + ";
        }
        out << ")";
        if (i + 1 < clauses.size())
            out << " * ";
    }

    return {out.str(), n_vars};
}

/**
 * @brief Main function to test CNF validity checker
 * 
 * Reads a CNF file and outputs:
 * - Whether the formula is valid (all clauses are tautologies)
 * - Number of valid clauses
 * - Number of invalid clauses
 * 
 * @return int Program exit status (0 for success)
 */
int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "File path required" << std::endl;
        return 1;
    }

    std::string path = argv[1];
    std::pair<std::string, int> to_string = cnfToString(path);

    int n_vars = to_string.second;

    // Convert to a parse tree (test time and memory)
    auto start = steady_clock::now();
    auto root = FxParser{}.parse_pipeline(to_string.first);
    auto end = steady_clock::now();
    auto time_taken_to_parse = duration_cast<milliseconds>(end - start);

    // Some parse tree operations (test time) [Height, evaluation]
    start = steady_clock::now();
    int height = compute_height(root.get());
    end = steady_clock::now();
    auto time_to_calc_height = duration_cast<nanoseconds>(end - start);

    std::unordered_map<std::string, bool> env_map = {};
    for (int i = 1; i <= n_vars; i++) {
        env_map[std::to_string(i)] = false;
    }
    start = steady_clock::now();
    bool eval_res = Evaluator {env_map}.evaluate(root.get());
    end = steady_clock::now();
    auto time_to_eval = duration_cast<nanoseconds>(end - start);

    // Validity checker (test time)
    start = steady_clock::now();
    int n = cnf_validcno(path);
    bool ans = cnf_validitychecker(path);
    end = steady_clock::now();
    auto time_to_validate = duration_cast<milliseconds>(end - start);


    // Output of util functions;
    if(ans == true) cout<<"Valid" << endl;
    else cout<< "Invalid"<< endl;
    cout<< "No of valid clauses: " << n << endl;
    cout<< "No of invalid clauses: " << cnf_non_valid_cno(path)<<endl;

    std::cout << "Height of parse tree: " << height << std::endl;
    std::cout << "Evaluation result on all false atoms: " << 0 << std::endl;

    // Time analysis
    std::cout << "---TIME ANALYSIS---" << std::endl;
    std::cout << "Time to convert to parse tree: " << time_taken_to_parse<< std::endl;
    std::cout << "Time to calculate height: " << time_to_calc_height << std::endl;
    std::cout << "Time to evaluate: " << time_to_eval << std::endl;
    std::cout << "Time to validate: " << time_to_validate << std::endl;
}