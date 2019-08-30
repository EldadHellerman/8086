InputFile = test
OutputPath = Debug
COMPort = 13
BuadRate = 400000

.PHONY: all upload dump clean

#all: $(OutputPath)\$(InputFile).o upload dump
all: $(OutputPath)\$(InputFile).o

$(OutputPath)\$(InputFile).o: $(InputFile).asm lcd.asm RGB_LCD.asm font.asm
	@nasm $< -o $@

upload: $(OutputPath)\$(InputFile).o
	@Programmer.exe upload -i'$(OutputPath)\$(InputFile).o' -c$(COMPort) -b$(BuadRate)

dump:
	@Programmer.exe dump -o'$(OutputPath)\dump.bin' -c$(COMPort) -b$(BuadRate)

clean:
	del $(OutputPath)\$(InputFile).o