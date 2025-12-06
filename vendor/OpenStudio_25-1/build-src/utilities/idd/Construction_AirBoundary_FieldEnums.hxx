/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CONSTRUCTION_AIRBOUNDARY_FIELDENUMS_HXX
#define UTILITIES_IDD_CONSTRUCTION_AIRBOUNDARY_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Construction_AirBoundaryFields
 *  \brief Enumeration of Construction:AirBoundary's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Construction_AirBoundaryFields, )
#else
class Construction_AirBoundaryFields: public ::EnumBase<Construction_AirBoundaryFields> {
 public: 
  enum domain 
  {
Name, AirExchangeMethod, SimpleMixingAirChangesperHour, SimpleMixingScheduleName,   };
  Construction_AirBoundaryFields()
   : EnumBase<Construction_AirBoundaryFields>(Name) {} 
  Construction_AirBoundaryFields(const std::string &t_name) 
   : EnumBase<Construction_AirBoundaryFields>(t_name) {} 
  Construction_AirBoundaryFields(int t_value) 
   : EnumBase<Construction_AirBoundaryFields>(t_value) {} 
  static std::string enumName() 
  { return "Construction_AirBoundaryFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Construction_AirBoundaryFields>::integer_value()); }
   private:
    friend class EnumBase<Construction_AirBoundaryFields>;
    typedef std::pair<std::string, int> PT;
    typedef std::vector<PT> VecType;
    static VecType buildStringVec(bool isd)
    {
      struct evalue
      {
        int value; const char *name; const char *description;
      };
      const evalue a[] =
      {
{ Construction_AirBoundaryFields::Name, "Name", "Name"},
{ Construction_AirBoundaryFields::AirExchangeMethod, "AirExchangeMethod", "Air Exchange Method"},
{ Construction_AirBoundaryFields::SimpleMixingAirChangesperHour, "SimpleMixingAirChangesperHour", "Simple Mixing Air Changes per Hour"},
{ Construction_AirBoundaryFields::SimpleMixingScheduleName, "SimpleMixingScheduleName", "Simple Mixing Schedule Name"},
        { 0,0,0 }
      };
      VecType v;
      int i = 0;
      while (!(a[i].value == 0 && a[i].name == 0 && a[i].description == 0))
      {
        if (isd)
        {
          std::string description = a[i].description; 
          if (!description.empty())
          {
            v.push_back(PT(description, a[i].value));
          }
        } else {
          v.push_back(PT(a[i].name, a[i].value));
        }
        ++i;
      }
      return v;
    }
  
  };
  inline std::ostream &operator<<(std::ostream &os, const Construction_AirBoundaryFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Construction_AirBoundaryFields> OptionalConstruction_AirBoundaryFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CONSTRUCTION_AIRBOUNDARY_FIELDENUMS_HXX
