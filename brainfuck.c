#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

size_t limit = 30000;

enum TokenType {
  INC_P = '>',
  DEC_PR = '<',
  INC_V = '+',
  DEC_V = '-',
  WRITE = '.',
  READ = ',',
  LOOP_BEGIN = '[',
  LOOP_END = ']',
};

typedef struct {
  enum TokenType t;
  int jump;
} Token;

void tokenize(char *prg, ssize_t len, Token *ts);
void eval(Token *ts, ssize_t len);

int main() {
  char *buf;
  ssize_t len;

  Token ts[30000];

  for (;;) {
    printf(">> ");
    if ((len = getline(&buf, &limit, stdin)) == EOF) {
      return 1;
    }
    if (buf[len - 1] == '\n') {
      buf[--len] = '\0';
    }
    tokenize(buf, len, ts);
    eval(ts, len);
    printf("\n");
  }

  return 0;
}

void tokenize(char *prg, ssize_t len, Token *ts) {
  int s[15000];
  int *sp = s;

  for (int i = 0; i < len; i++) {
    char c = prg[i];
    Token t = {c, 0};
    ts[i] = t;

    int j;
    switch (c) {
    case '[':
      s[*sp] = i;
      sp++;
      break;
    case ']':
      j = s[*sp];
      ts[i].jump = j;
      ts[j].jump = i + 1;
      sp--;
      break;
    }
  }
}

void eval(Token *ts, ssize_t len) {
  char buf[30000];
  char *p = buf;

  for (int i = 0; i < len; i++) {
    Token t = ts[i];
    /* printf("%d %d\n", i , t.t); */
    switch (t.t) {
    case '>':
      p++;
      break;
    case '<':
      p--;
      break;
    case '+':
      (*p)++;
      break;
    case '-':
      (*p)--;
      break;
    case '.':
      putchar(*p);
      break;
    case ',':
      *p = getchar();
      break;
    case '[':
      if (*p == 0) {
        i = t.jump - 1;
      }
      break;
    case ']':
      i = t.jump - 1;
      break;
    }
  }
}
