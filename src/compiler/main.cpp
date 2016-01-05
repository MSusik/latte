//
// Created by msusik on 11.12.15.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include <boost/filesystem.hpp>

#include "../Absyn.H"
#include "../Parser.H"
#include "Skeleton.H"
#include "CorrectnessChecker.H"
#include "FunctionRetriever.h"
#include "Compiler.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::vector;

const string outer_compiler = "clang";
const string runtime = "/src/runtime.c";

void compile_target(const string &full_without_extension, const char* first_argv){
    // filename "bat" for "sth/bat.lat" path
    // "bat.s" already exists
    stringstream command;
    boost::filesystem::path full_path( boost::filesystem::initial_path() );
    full_path = boost::filesystem::system_complete( boost::filesystem::path( first_argv ) );
    command << outer_compiler << " -w -o " << full_without_extension << " " << full_without_extension << ".s "
            << full_path.parent_path() << runtime;

    int i = system(command.str().c_str());
    if(i != 0)
        cout << "UPS!" << endl;
}

void create_stub(const string &full_without_extension){

    std::ofstream outfile (full_without_extension + ".s");
    outfile << R"(.globl main
label0:
        .asciz "hello world"
main:
        pushq %rbp
        mov %rsp, %rbp
        movq $label0, %rdi
        call printString
        mov $0, %eax
        popq %rbp
        ret
)" << std::endl;
    outfile.close();
}

int main(int argc, char ** argv) {
    FILE *input;
    boost::filesystem::path path;
    if (argc > 1)
    {
        path = boost::filesystem::path(argv[1]);
        input = fopen(argv[1], "r");
        if (!input)
        {
            fprintf(stderr, "Error opening input file.\n");
            exit(1);
        }
    }
    else
    {
        cout << "Usage ./latc_x86_64 <latte file>.lat" << endl;
        exit(1);
    }

    string parent_path = path.parent_path().string();
    string filename = path.stem().string();
    string full_without_extension;
    if(parent_path.size()) {
        full_without_extension = parent_path + "/" + filename;
    }
    else {
        full_without_extension = "./" + filename;
    }

    Prog *parse_tree = static_cast<Prog*>(pProgram(input));

    if (parse_tree)
    {
        vector<FnDef*> functions;
        map<string, string> string_to_label;
        FunctionRetriever fr(parse_tree);
        functions = fr.getFunctions();

        CorrectnessChecker type_checker(functions, string_to_label);
        type_checker.check_types();
        ErrorState error = type_checker.error;

        if(error.error)
        {
            cerr << "ERROR" << endl;
            for(auto it=error.messages.begin(); it != error.messages.end(); ++it)
                error.printMessage(*it);
            flush(cerr);
        }
        else
        {
            string assembly_file_name = full_without_extension + ".s";
            Compiler compiler(functions, assembly_file_name, string_to_label);
            compiler.generate();

            //create_stub(full_without_extension);

            // name?
            //compile_target(full_without_extension, argv[0]);

            cerr << "OK" << endl;
            flush(cerr);
            return 0;
        }
    }
    return 1;
}