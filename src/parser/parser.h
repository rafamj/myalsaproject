//parser.h
#include <string>
#include <fstream>
#include "table.h"

using namespace std;

class AlsaSeq;
class AlsaOut;
class AlsaIn;
class DevObjSet;
class DeviceSet;

enum Type {UNKNOWN,IDENTIFIER, NUMBER, SPECIAL, EOL, END,CONNECT,STRING};

class Token {
  public:
  Type type;
  string name;
  Token(Type ty, string n) {type=ty;name=n;};
  bool is(char c) {return name[0]==c;}
  bool is(Type ty) {return type==ty;}
  void print();
};

class Parser{
  bool saveText; //if true the text of a def is saved
  string text;
  string line;
  size_t textIndex;
  size_t errorIndex;
  int nLine;
  Table table;
  Token *nextT;
  void initString(string s);
  void initDevices();
  void printError(const char *error);
  void printError(const char *error, const char *more);
  void expect(char c);
  Token *expect(Type t);
  void jumpBlanks();
  void nextLine();
  void readDef();
  vector<unsigned int> readIntArray(Symbol *s);
  //Device *createDev(string typeName,vector<Symbol *> paramDefs, vector<Symbol *> &init);
  Device *createDev(string typeName, vector<Symbol *> &init);
  DevObj *createDev(string name, DevDef *dev, vector<Symbol *> init);
  //void modifyDev(DevObj *devObj, vector<Symbol *> init);
  Symbol *createConstant(sample value);
  void initParameters(DevDef *def,  DevObj *obj,vector<Symbol *> &init);
  Symbol *create(string typeName, string name, vector<Symbol *> init);
  Symbol *create(string typeName, string name,vector<int> dimensions, vector<Symbol *> init);
  Symbol *createDevDef(string name, string init, string input, string output, bool d=true,string body="", int nLine=0); 
  //Symbol *createDevDef(string name, vector<Symbol *> in, vector<Symbol *> inp, vector<Symbol *> outp, bool d, string body, size_t textIndex, int nLine); 
  int readSlice(int &begin, int &end);
  Symbol *processIO(Symbol *s, string name);
  void assignParameters(Symbol *s, vector<Symbol *>parameters);
  Symbol *readVar(Token *t);
  Symbol *createOperation1(string op,Symbol *a, Symbol *b);
  Symbol *createOperation(string op,Symbol *a, Symbol *b);
  Symbol *sum(Symbol *a, Symbol *b); 
  Symbol *substract(Symbol *a, Symbol *b); 
  Symbol *readSum();
  Symbol *multiply(Symbol *a, Symbol *b); 
  Symbol *divide(Symbol *a, Symbol *b); 
  Symbol *readProduct();
  vector<Symbol *> readCommaSeparatedExp(char end,bool readVars=false, bool admitNull=false);
  Symbol *readArray(bool readVars=false);
  Symbol *mean(Symbol *a);
  Symbol *readValue();
  Symbol *readExpression();
  vector<Symbol *> readDeclaration(string type);
  void assign(Symbol *left, Symbol *right);
  void connect(Symbol *left, Symbol *right);
  string readLine();
  string readIdentifier();
  string readNumber();
  string readChar();
  void readComment(char first);
  string readString();
  Token *nextToken(); 
  Token *lookAhead() {return nextT;}
  void list(DevObj *devObj, bool defining);////
  DevObjSet *set;
  public:
  AlsaSeq *aseq;
  AlsaOut *asound;
  AlsaIn *aIn;
  Parser();
  Parser(ifstream fs);
  void initFile(string filename);
  void parse(string end);
  void getDevices(DeviceSet *d);
  void buildDeviceSet(string root,bool defining);
  void buildDeviceSet(DevObj *devObj,bool defining);
  ~Parser();
};

