cls
@cd %~dp0
@echo replace.exe 12312312345.txt out.txt 1231234 cool
@echo.
@..\Debug\replace.exe 12312312345.txt out.txt 1231234 cool
@echo.
@echo.
@echo replace.exe mama.txt out.txt ma mama
@echo.
@..\Debug\replace.exe mama.txt out.txt ma mama
@echo.
@echo.
@echo replace.exe text.txt out.txt ����� 123
@echo.
@..\Debug\replace.exe text.txt out.txt ����� 123
@echo.
@echo.
@fsutil file createnew big.txt 3147483648
@echo.
@echo replace.exe big.txt out.txt 1 2
@echo.
@..\Debug\replace.exe big.txt out.txt 1 2
@echo.
@echo.
@echo replace.exe 12312312345.txt big.txt 1 2
@echo.
@..\Debug\replace.exe 12312312345.txt big.txt 1 2
del big.txt
@echo.
@echo.
@echo replace.exe empty.txt out.txt 1 2
@echo.
@..\Debug\replace.exe empty.txt out.txt 1 2
@echo.
@echo.
@echo replace.exe none.txt out.txt 1 2
@echo.
@..\Debug\replace.exe none.txt out.txt 1 2
@echo.
@echo param count != 4
@echo.
@..\Debug\replace.exe

