. A2 CHLOE KERSHNER, WINNIE THONG cssc4063 CS530 SPRING 2024
0100    TEST      START   100
0100    BEGIN     LDA    #5                    010000
0103              STA     ALPHA                0F2007
0106             +LDA     NTY                  03100111
010A              STCH    C1                   572003
010D    ALPHA     RESW    1                   
0110    C1        RESB    1                   
0111    NTY       BYTE    X'90'                90
                  END     BEGIN
