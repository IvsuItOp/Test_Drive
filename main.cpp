#include <QApplication>
#include <QMessageBox>
#include "Dictionary.h"

int main(int argc, char *argv[])
  {
  QApplication a(argc, argv);
  try
    {
    Dictionary D( "Open first text" ), D1(  "Open second text" );
    D >> "Frequency dictionary " + D.m_FileName;
    D1 >> "Frequency dictionary " + D1.m_FileName;
    ( D & D1 ) >> "Intersection dictionaries " + D.m_FileName + " and " + D1.m_FileName;
    ( D | D1 ) >> "Combining dictionaries " + D.m_FileName + " and " + D1.m_FileName;
    ( D - D1 ) >> "Difference " + D.m_FileName + " and " + D1.m_FileName;
    ( D1 - D ) >>  "Difference  " + D1.m_FileName + " and " + D.m_FileName;
    ( D1 ^ D ) >> "Symmetrical difference " + D.m_FileName + " and " + D1.m_FileName;
    }
  catch( QByteArray Err )
    {
    QMessageBox::information( NULL, "Error!", Err );
    }
  return 0;
  }
