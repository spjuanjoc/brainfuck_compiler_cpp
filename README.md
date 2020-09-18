# Brainfuck Compiler


From the C++ on Sea talk by Sy Brand about a
[Cross-platform compiler](https://youtu.be/Jw2n5QSul34)
on how to write a compiler for the language Brainfuck
(see [Brainfuck](https://en.wikipedia.org/wiki/Brainfuck)
)

Commands available

|Character|Meaning|
|:---:|---|
|\>| Incrementa el puntero.|
|<| Decrementa el puntero.|
|+| Incrementa el byte apuntado.|
|-| Decrementa el byte apuntado.|
|.| Escribe el byte apuntado en el flujo de salida.|
|,| Lee un byte del flujo de entrada y lo almacena en el byte apuntado.|
|[| Avanza a la instrucción inmediatamente posterior al ] correspondiente si el byte actualmente apuntado es nulo (si es 0).|
|]| Retrocede a la instrucción inmediatamente posterior al [ correspondiente si el byte actualmente apuntado no es nulo (si es distinto de 0)|

---
Requires `nasm`

    sudo apt install -y nasm