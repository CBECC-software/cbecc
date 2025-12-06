/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_DAYLIGHTING_REFERENCEPOINT_FIELDENUMS_HXX
#define UTILITIES_IDD_DAYLIGHTING_REFERENCEPOINT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Daylighting_ReferencePointFields
 *  \brief Enumeration of Daylighting:ReferencePoint's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Daylighting_ReferencePointFields, )
#else
class Daylighting_ReferencePointFields: public ::EnumBase<Daylighting_ReferencePointFields> {
 public: 
  enum domain 
  {
Name, ZoneorSpaceName, XCoordinateofReferencePoint, YCoordinateofReferencePoint, ZCoordinateofReferencePoint,   };
  Daylighting_ReferencePointFields()
   : EnumBase<Daylighting_ReferencePointFields>(Name) {} 
  Daylighting_ReferencePointFields(const std::string &t_name) 
   : EnumBase<Daylighting_ReferencePointFields>(t_name) {} 
  Daylighting_ReferencePointFields(int t_value) 
   : EnumBase<Daylighting_ReferencePointFields>(t_value) {} 
  static std::string enumName() 
  { return "Daylighting_ReferencePointFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Daylighting_ReferencePointFields>::integer_value()); }
   private:
    friend class EnumBase<Daylighting_ReferencePointFields>;
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
{ Daylighting_ReferencePointFields::Name, "Name", "Name"},
{ Daylighting_ReferencePointFields::ZoneorSpaceName, "ZoneorSpaceName", "Zone or Space Name"},
{ Daylighting_ReferencePointFields::XCoordinateofReferencePoint, "XCoordinateofReferencePoint", "X-Coordinate of Reference Point"},
{ Daylighting_ReferencePointFields::YCoordinateofReferencePoint, "YCoordinateofReferencePoint", "Y-Coordinate of Reference Point"},
{ Daylighting_ReferencePointFields::ZCoordinateofReferencePoint, "ZCoordinateofReferencePoint", "Z-Coordinate of Reference Point"},
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
  inline std::ostream &operator<<(std::ostream &os, const Daylighting_ReferencePointFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Daylighting_ReferencePointFields> OptionalDaylighting_ReferencePointFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_DAYLIGHTING_REFERENCEPOINT_FIELDENUMS_HXX
