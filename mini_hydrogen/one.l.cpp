%{
int lines = 0, spaces = 0, tabs = 0, other = 0;
%}

%%
\n      { lines++; }
" "     { spaces++; }
\t      { tabs++; }
.       { other++; }
%%

int main() {
    yylex();
    printf("Lines: %d\n", lines);
    printf("Spaces: %d\n", spaces);
    printf("Tabs: %d\n", tabs);
    printf("Other characters: %d\n", other);
    return 0;
}
