#include <qtextstream.h>
#include <qfile.h>
#include <QFileDialog>
#include "Dictionary.h"

Dictionary::Dictionary( char *Message )
  {
  if( Message == NULL ) return;
  QString FileName = QFileDialog::getOpenFileName( NULL, Message, "", "Text files (*.txt)");
  if( FileName.isEmpty() ) throw QByteArray( "Have changed your mind to work" );
  m_FileName = FileName.right( FileName.length() - FileName.lastIndexOf( '/' ) - 1 );
  QFile File( FileName );
  if( !File.open( QIODevice::ReadOnly | QIODevice::Text ) ) throw QByteArray( "File " ) + FileName + " was not open!";
  QTextStream Fin( &File );
  for( ; !Fin.atEnd(); )
    {
    QString WordIn, Word;
    Fin >> WordIn;
    for( int iChar = 0; iChar < WordIn.size(); iChar++ )
      {
      QChar Char = WordIn[iChar];
      if( Char < 'А' || Char > 'я' ) break;
        Word += Char.toLower();
      }
    if( Word.isEmpty() ) continue;
    ( *this )[Word]++; //2
    }
  }

Dictionary::Dictionary( const SetString& Words )
  {
  for( auto pW = Words.begin(); pW != Words.end() && !pW->isEmpty(); pW++ ) //1
    ( *this )[*pW]; //2
  }

void Dictionary::operator >> ( const QString& Message )
  {
  QString FileName = QFileDialog::getSaveFileName( NULL, Message, "", "Text files (*.txt)" );
  if( FileName.isEmpty() ) throw QByteArray( "Have changed your mind to work" );
  QFile File( FileName );
  if( !File.open( QIODevice::WriteOnly | QIODevice::Text ) ) throw QByteArray( "File " ) + FileName + " was not open!";
  QTextStream Fout( &File );
  Fout << Message << endl;
  int iWord = 1;
  for( Dictionary::iterator pW = begin(); pW != end(); pW++, iWord++ ) //3
    Fout << iWord << '\t' << pW.key() << '\t' << pW.value() << endl;
  }

SetString::SetString( const Dictionary& D )
  {
  for( auto pW = D.begin(); pW != D.end(); pW++ )
    insert( pW.key() );
  }


Dictionary Dictionary::operator & ( const Dictionary& D )
  {
  SetString SetMy( *this ), SetD( D );
  SetMy &= SetD;
  return SetMy;
  }

Dictionary Dictionary::operator | ( const Dictionary& D )
  {
  SetString SetMy( *this ), SetD( D );
  SetMy |= SetD;
  return SetMy;
  }

Dictionary Dictionary::operator - ( const Dictionary& D )
  {
  SetString SetMy( *this ), SetD( D );
  SetMy -= SetD;
  return SetMy;
  }

Dictionary Dictionary::operator ^ ( const Dictionary& D )
  {
  SetString SetMy( *this ), SetD( D );
  return ( SetMy - SetD ) | ( SetD - SetMy );
  }
