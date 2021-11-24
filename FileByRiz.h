#pragma once
#include <iostream>

class File
{
    private:
    FILE *fp;
    std::string nomeFile;

    public:
    File(std::string pNomeFile)
    {
        nomeFile = pNomeFile;
    }

    void WriteToFile(std::string dati, const char metod[])
	{
		int err = fopen_s(&fp, nomeFile.c_str(), metod);
		if (err == 0)
		{
			fprintf(fp, "%s", dati.c_str());
			fclose(fp);
		}
	}

	void WriteLineToFile(std::string dati, const char metod[])
	{
		int err = fopen_s(&fp, nomeFile.c_str(), metod);
		if (err == 0)
		{
			fprintf(fp, "%s\n", dati.c_str());
			fclose(fp);
		}
	}

    void ChangeLine(std::string dati, int line)
    {
		if(line <= 0) line = 1;

		if(dati != ReadLineOfFile(line) && (line <= ReturnNumbersLine()))
		{
			std::string file = "";
        
			for(int i = 0; i < (line - 1); i++)
			{
				file += ReadLineOfFile(i);
			}
			
			file += dati;
			if (ReturnNumbersLine() != line)
				file += "\n";

			for(int i = line; i < ReturnNumbersLine(); i++)
			{
				file += ReadLineOfFile(i);
			}

			WriteToFile(file, "w");
		}
    }

    std::string ReadAllFile()
	{
		std::string dati = "";

		int err = fopen_s(&fp, nomeFile.c_str(), "r");
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


    std::string ReadLineOfFile(int line)
    {
        std::string dati = "";
        char buffer[1024];
        int cont = 0;

        int err = fopen_s(&fp, nomeFile.c_str(), "r");
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

		int err = fopen_s(&fp, nomeFile.c_str(), "r");
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