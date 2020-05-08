# Terminal Paint
## Hands on Project
This project is intended to familiarize new members with C programming using a fun and interactive project.
## Usage
Build with `make` and type the command `CREATE <W,H>` to start operating on a WxH PGM file. Here is what you can do:
|CREATE <width> <heigth>: Esse comando deve criar uma
estrutura que permita a manipulação de uma imagem PGM de
dimensões width x height

| Commands |                 Arguments\*                 |
| -------- | :----------------------------------------: |
| `EXPORT`   |               *\<file name\>*                |
| `POINT`    |           *\<x\> \<y\> \<color\>*            |
| `LINE`     |   *\<x1\> \<y1\> \<x2\> \<y2\> \<color\>*    |
| `CIRCLE`   |      *\<x\> \<y\> \<radius\> \<color\>*      |
| `DISK`     |      *\<x\> \<y\> \<radius\> \<color\>*      |
| `RECT`     | *\<x\> \<y\> \<width\> \<height\> \<color\>* |
| `EXIT`     |                                            |

  \* Arguments are SPACE SEPARATED INTEGERS. And color is a grey scale (0 = black)