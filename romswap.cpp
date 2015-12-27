#include <stdio.h>
#include <stdint.h>
#include <string>

enum class swapmode
{
    BITS16,
    BITS32,
    BITS64,
    UNDEFINED
};

struct config
{
    swapmode mode;
};

config parseconfig(char* cfgfn)
{
    config res;
    FILE* fp = fopen(cfgfn,"r");
    while(!feof(fp))
    {
        std::string property;
        int c = fgetc(fp);
        while(c != '=')
        {
            if(c == EOF)
            {
                fclose(fp);
                return res;
            }
            if(c != ' ' && c != '\t' && c != '\r' && c != '\n')
            {
                property.push_back(c);
            }

            c = fgetc(fp);
        }
        std::string value;
        c = fgetc(fp);
        while(c != ';')
        {
            if(c == EOF)
            {
                fclose(fp);
                return res;
            }
            if(c != ' ' && c != '\t' && c != '\r' && c != '\n')
            {
                value.push_back(c);
            }

            c = fgetc(fp);
        }

        if(property == "mode")
        {
            if(value == "16bits") res.mode = swapmode::BITS16;
            else if(value == "32bits") res.mode = swapmode::BITS32;
            else if(value == "64bits") res.mode = swapmode::BITS64;
            else res.mode = swapmode::UNDEFINED;
        }
    }

    fclose(fp);

    return res;
}

int main(int ac, char** av)
{
    if(ac<3) return 1;

    if(ac==3)
    {
        FILE* in = fopen(av[1],"rb");
        FILE* out = fopen(av[2],"wb");

        //Figure out the size of the input file.
        fseek(in,0,SEEK_END);
        long pos = ftell(in);
        fseek(in,0,SEEK_SET);

        for(int i = 0; i<pos; i+=2)
        {
            uint8_t tmp_lo;
            uint8_t tmp_hi;
            tmp_lo = fgetc(in);
            tmp_hi = fgetc(in);
            fputc(tmp_hi,out);
            fputc(tmp_lo,out);
        }

        fclose(in);
        fclose(out);
    }
    else
    {
        config cfg = parseconfig(av[1]);
        FILE* in = fopen(av[2],"rb");
        FILE* out = fopen(av[3],"wb");

        //Figure out the size of the input file.
        fseek(in,0,SEEK_END);
        long pos = ftell(in);
        fseek(in,0,SEEK_SET);

        if(cfg.mode == swapmode::BITS16)
        {
            for(int i = 0; i<pos; i+=2)
            {
                uint8_t tmp_lo;
                uint8_t tmp_hi;
                tmp_lo = fgetc(in);
                tmp_hi = fgetc(in);
                fputc(tmp_hi,out);
                fputc(tmp_lo,out);
            }
        }
        else if(cfg.mode == swapmode::BITS32)
        {
            for(int i = 0; i<pos; i+=4)
            {
                uint8_t tmp1;
                uint8_t tmp2;
                uint8_t tmp3;
                uint8_t tmp4;
                tmp1 = fgetc(in);
                tmp2 = fgetc(in);
                tmp3 = fgetc(in);
                tmp4 = fgetc(in);
                fputc(tmp4,out);
                fputc(tmp3,out);
                fputc(tmp2,out);
                fputc(tmp1,out);
            }
        }
        else if(cfg.mode == swapmode::BITS64)
        {
            for(int i = 0; i<pos; i+=8)
            {
                uint8_t tmp1;
                uint8_t tmp2;
                uint8_t tmp3;
                uint8_t tmp4;
                uint8_t tmp5;
                uint8_t tmp6;
                uint8_t tmp7;
                uint8_t tmp8;
                tmp1 = fgetc(in);
                tmp2 = fgetc(in);
                tmp3 = fgetc(in);
                tmp4 = fgetc(in);
                tmp5 = fgetc(in);
                tmp6 = fgetc(in);
                tmp7 = fgetc(in);
                tmp8 = fgetc(in);
                fputc(tmp8,out);
                fputc(tmp7,out);
                fputc(tmp6,out);
                fputc(tmp5,out);
                fputc(tmp4,out);
                fputc(tmp3,out);
                fputc(tmp2,out);
                fputc(tmp1,out);
            }
        }

        fclose(in);
        fclose(out);
    }
}
