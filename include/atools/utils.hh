#ifndef __UTILS_HH__
#define __UTILS_HH__

#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>

#include <cctype> // For ::toupper and ::tolower.

#include <atools/blind.hh>

class Amplitude;
class ConfigFile;
class FunctionMinimum;
class MnUserParameters;
class MnUserCovariance;
class Parameter;
class Coef;
class MinimizerExpr;
class FunctionMinimum;

class Utils
{
public:
  template <class T>
  static T fromStr( const std::string& str )
  {
    std::istringstream tempStr( str );
    T num;
    if ( tempStr >> num )
      return num;

    return Blind( 4 ).unblind< double >( str );
  }

  template <class T>
  static std::string toStr( const T& val, const int& digits = 0 )
  {
    std::ostringstream tempStr;
    if ( digits )
      tempStr << std::setfill( '0' ) << std::setw( digits );

    if ( tempStr << val )
      return tempStr.str();

    return "";
  }


  static const unsigned hash( const std::string& input );
  static const unsigned hash( const Amplitude&   amp   );

  static const std::string replace( const std::string& str, const std::string& pattern, const std::string& replacement );
  static const std::string conjugate( const std::string& str );
  static const std::string charge   ( const std::string& str );
  static const std::string nosigns  ( const std::string& str );

  static const std::string toupper( std::string str )
  {
    std::transform( str.begin(), str.end(), str.begin(), ::toupper );

    return str;
  }

  static const std::string tolower( std::string str )
  {
    std::transform( str.begin(), str.end(), str.begin(), ::tolower );

    return str;
  }

  static       bool startsWith( const std::string& str, const std::string& start );
  static       bool endsWith  ( const std::string& str, const std::string& end   );
  static       bool contains  ( const std::string& str, const std::string& subst );

  template <class T>
  static       bool contains  ( const std::vector< T >& vec, const T& value )
  {
    for ( const T& entry : vec )
      if ( entry == value )
        return true;

    return false;
  }

  static const int         precision( const double& value, const int& digits = 20 );
  static const std::string getOutput( const FunctionMinimum&  min  );
  static const std::string getOutput( const MnUserParameters& pars );
  static const std::string getOutput( const MnUserParameters& pars, const MnUserCovariance& cov );

  static const Parameter   makePar ( const std::string& name, std::string info        );
  static const Parameter   makePar ( const ConfigFile&  file, const std::string& name );
  static const Parameter   makePar ( const ConfigFile&  file, const std::string& section, const std::string& name );
  static const Parameter   makePar ( const ConfigFile&  file, const std::string& section, const std::string& name, const std::string& kstype );

  static const Coef        makeCoef( const ConfigFile&  name, const std::string& re  , const std::string& im );

  static const double      residual( const double& datum, const double& pdf );

  static void              contour( const unsigned& sigmas,
                                    const std::string& outnameM, const std::string& outnameP,
                                    MinimizerExpr& nlls, const FunctionMinimum& min );
};


#endif
