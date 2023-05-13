#include <sstream>
#include "StreamTable.h"
#include "ExcelStream.h"

void TestStreamTable2()
{
    //открываем
    ExcelLoader xls;
    xls.LoadExcel("C:/log.xlsx", 1);

    excelstream os(xls.range_, 1, 1);//координаты левого верхнего угла

    StreamTable st(os);
    st.SetCols(4);//todo: задание ширины Excel-ячеек пока не реализовано

    st.MakeBorderExt(false);//обязательно, иначе будут лишние пустые строки
    st.SetDelimRow(false);//обязательно, иначе будут лишние пустые строки
    st.SetDelimCol(true, excel_stringbuf::colDelim);//обязательно, т.к. excel_stringbuf разбивает строку по столбцам с учетом colDelim

    //заголовок таблицы
    st << "#" << "Property" << "Value" << "Unit";

    enum { nr = 10 };
    for (int i = 0; i < nr; i++) {
        st << i + 1 << "Prop" << i << "Unit";
    }

    os.flush();