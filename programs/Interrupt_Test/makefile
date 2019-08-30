InputFile = interrupt
OutputPath = Debug
COMPort = 5
BuadRate = 230400

.PHONY: all upload dump clean

all: $(OutputPath)\$(InputFile).o upload dump

$(OutputPath)\$(InputFile).o: $(InputFile).asm
	@nasm $< -o $@

upload: $(OutputPath)\$(InputFile).o
	@Programmer.exe upload -i'$(OutputPath)\$(InputFile).o' -c$(COMPort) -b$(BuadRate)

dump:
	@Programmer.exe dump -o'$(OutputPath)\dump.bin' -c$(COMPort) -b$(BuadRate)

clean:
	del $(OutputPath)\$(InputFile).o