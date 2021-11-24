#pragma once
#include <iostream>

class File
{
    private:
    FILE *fp;
    std::string nameFile;

    public:
    File(std::string pNameFile)
    {
        nameFile = pNameFile;
    }

    void Write(std::string dati, const char metod[])
	{
		int err = fopen_s(&fp, nameFile.c_str(), metod);
		if (err == 0)
		{
			fprintf(fp, "%s", dati.c_str());
			fclose(fp);
		}
	}

	void WriteLine(std::string dati, const char metod[])
	{
		int err = fopen_s(&fp, nameFile.c_str(), metod);
		if (err == 0)
		{
			fprintf(fp, "%s\n", dati.c_str());
			fclose(fp);
		}
	}

    void ChangeLine(std::string dati, int line)
    {
		if(line <= 0) line = 1;

		if(dati != ReadLine(line) && (line <= ReturnNumbersLine()))
		{
			std::string file = "";
        
			for(int i = 0; i < (line - 1); i++)
			{
				file += ReadLine(i);
			}
			
			file += dati;
			if (line != ReturnNumbersLine())
				file += "\n";

			for(int i = line; i < ReturnNumbersLine(); i++)
			{
				file += ReadLine(i);
			}

			Write(file, "w");
		}
    }

    std::string ReadAllFile()
	{
		std::string dati = "";

		int err = fopen_s(&fp, nameFile.c_str(), "r");
		if (err == 0)
		{
			while (!feof(fp))
			{
				char buffer = fgetc(fp);
				if (feof(fp) && (buffer == '\n'))
					break;

				dati += buffer;
			}
			fclose(fp);
		}
		else
			std::cout << "Impossibile aprire file!";

		return dati;
	}


    std::string ReadLine(int line)
    {
        std::string dati = "";
        char buffer[1024];
        int cont = 0;

        int err = fopen_s(&fp, nameFile.c_str(), "r");
        if(err == 0)
        {
            while (!feof(fp))
            {
                fgets(buffer, 1024, fp);
                if(cont == line)
                {
                    dati += buffer;
                    break;
                }
                
                cont++;
            }
            fclose(fp);
        }
        else
        {
            std::cout << "Impossibile aprire il file !";
        }

        return dati;
    }

    int ReturnNumbersLine()
	{
		int cont = 0;
		char buffer[1024];

		int err = fopen_s(&fp, nameFile.c_str(), "r");
		if (err == 0)
		{
			while (!feof(fp))
			{
				fgets(buffer, 1024, fp);
				cont++;
			}
			fclose(fp);
		}
		else
			std::cout << "Impossibile aprire file!";

		return cont;
	}
};
