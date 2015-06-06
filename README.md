### FCAL to C++ Translator 

A translator that takes a domain specific language, the FCAL (Forest Cover Analysis Language) code and converts it to proper C++ code.

This was a semester long project done in teams of 2 for a Program and Design Development class. All commits are intact along with my project partner, Sophia Stembridge. This repository was migrated from my private repository on my university's private GitHub repository.

The project was developed using the iterative model of development, with a total of 4 iterations. Automated testing ([CXXTest - the unit testing framework](cxxtest.com)) was also used to ensure for correctness. 

The translator is primarily made up of:

- Scanner (Regex Matching and token generation)
- Parser (Takes the linked list of tokens and creates nodes for the AST)
- AST (Abstract Syntax Tree that holds all the nodes in the proper hierarchy)

On a high level, the scanner generates the list of tokens, which the parser will convert into nodes and form the AST, and then 'translate' the code into a C++ equivalent during the unparsing.

## Usage

Now that we got out that out of the way, here's how to use the project.

1. Firstly either clone the repository or just download the releases/tags [here](https://github.com/leewc/fcal-cpp-translator/releases) with the `finalIter` being the most recent tag.

2. `cd` into `src` do one of the following : 
	- `make all` to compile all code incl tests
	- `make run_tests` to compile all code and execute the tests immediately
	- `make clean` to delete all compiled code

3. Refer to `codegeneration_tests.h`, `ast_tests.h` , `parser_tests.h` and `regex_tests.h` for additional driver code that calls the appropriate functions. You mainly want to refer to `codegeneration_tests.h` for the entire working of the program. I might make a driver file to tie it all in the future but no guarantees. (Probably won't do it soon as I have other things I want to work on).

4. There is also a `doxygen` file if you'd like to generate the documentation for it, we have added comments in a doxygen-friendly format. 

Lastly also refer to the `writing` folder for things like UML and the writing assignments (written and completed by only myself, this was not a group effort) on topics such as approaches used during the development of this academic project.

## Credits and Copyright

We received a lot of guidance in completing this project, as well as given help through starter code provided by the course instructor. As visible in many files, the project and starter code was created by Professor Erik Van Wyk and copyright belongs to him. Additional code written by the students are released under the [GNU GPL v2](http://www.gnu.org/licenses/gpl-2.0.txt) for personal use. 

**A precautionary note for students** that stumble upon this repository by searching for project solutions: **Do not blatantly copy** all the code. While it is open source for reference, using the code without providing attribution as well as claiming it as code written by yourself is plagiarism, which is grounds for failing an entire course. Yes I know you've heard of it, and probably won't listen if you're desperate, but you won't learn by copying code, and you risk getting caught (a lot of professors actually do enforce this rules, take it from me). Besides, if you don't know the in and outs of writing a language translator, you won't be able to properly do the quizzes and exams, even more so, this stuff is actually used in the industry. I didn't believe it too but the concepts I've learned from this project has been a recurring theme for some other things I've worked on. There's a fine line between referring, and blatantly copying. 

*On that note, instructors of this class please do not hesitate to contact me should the open source nature of this repo be an issue.*