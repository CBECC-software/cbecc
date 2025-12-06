/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRLOOPHVAC_EXHAUSTSYSTEM_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRLOOPHVAC_EXHAUSTSYSTEM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirLoopHVAC_ExhaustSystemFields
 *  \brief Enumeration of AirLoopHVAC:ExhaustSystem's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirLoopHVAC_ExhaustSystemFields, )
#else
class AirLoopHVAC_ExhaustSystemFields: public ::EnumBase<AirLoopHVAC_ExhaustSystemFields> {
 public: 
  enum domain 
  {
Name, ZoneMixerName, FanObjectType, FanName,   };
  AirLoopHVAC_ExhaustSystemFields()
   : EnumBase<AirLoopHVAC_ExhaustSystemFields>(Name) {} 
  AirLoopHVAC_ExhaustSystemFields(const std::string &t_name) 
   : EnumBase<AirLoopHVAC_ExhaustSystemFields>(t_name) {} 
  AirLoopHVAC_ExhaustSystemFields(int t_value) 
   : EnumBase<AirLoopHVAC_ExhaustSystemFields>(t_value) {} 
  static std::string enumName() 
  { return "AirLoopHVAC_ExhaustSystemFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirLoopHVAC_ExhaustSystemFields>::integer_value()); }
   private:
    friend class EnumBase<AirLoopHVAC_ExhaustSystemFields>;
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
{ AirLoopHVAC_ExhaustSystemFields::Name, "Name", "Name"},
{ AirLoopHVAC_ExhaustSystemFields::ZoneMixerName, "ZoneMixerName", "Zone Mixer Name"},
{ AirLoopHVAC_ExhaustSystemFields::FanObjectType, "FanObjectType", "Fan Object Type"},
{ AirLoopHVAC_ExhaustSystemFields::FanName, "FanName", "Fan Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirLoopHVAC_ExhaustSystemFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirLoopHVAC_ExhaustSystemFields> OptionalAirLoopHVAC_ExhaustSystemFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRLOOPHVAC_EXHAUSTSYSTEM_FIELDENUMS_HXX
