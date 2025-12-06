/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_UNITARYSYSTEMPERFORMANCE_MULTISPEED_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_UNITARYSYSTEMPERFORMANCE_MULTISPEED_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_UnitarySystemPerformance_MultispeedFields
 *  \brief Enumeration of OS:UnitarySystemPerformance:Multispeed's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UnitarySystemPerformance_MultispeedFields, )
#else
class OS_UnitarySystemPerformance_MultispeedFields: public ::EnumBase<OS_UnitarySystemPerformance_MultispeedFields> {
 public: 
  enum domain 
  {
Handle, Name, SingleModeOperation, NoLoadSupplyAirFlowRateRatio,   };
  OS_UnitarySystemPerformance_MultispeedFields()
   : EnumBase<OS_UnitarySystemPerformance_MultispeedFields>(Handle) {} 
  OS_UnitarySystemPerformance_MultispeedFields(const std::string &t_name) 
   : EnumBase<OS_UnitarySystemPerformance_MultispeedFields>(t_name) {} 
  OS_UnitarySystemPerformance_MultispeedFields(int t_value) 
   : EnumBase<OS_UnitarySystemPerformance_MultispeedFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UnitarySystemPerformance_MultispeedFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UnitarySystemPerformance_MultispeedFields>::integer_value()); }
   private:
    friend class EnumBase<OS_UnitarySystemPerformance_MultispeedFields>;
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
{ OS_UnitarySystemPerformance_MultispeedFields::Handle, "Handle", "Handle"},
{ OS_UnitarySystemPerformance_MultispeedFields::Name, "Name", "Name"},
{ OS_UnitarySystemPerformance_MultispeedFields::SingleModeOperation, "SingleModeOperation", "Single Mode Operation"},
{ OS_UnitarySystemPerformance_MultispeedFields::NoLoadSupplyAirFlowRateRatio, "NoLoadSupplyAirFlowRateRatio", "No Load Supply Air Flow Rate Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UnitarySystemPerformance_MultispeedFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UnitarySystemPerformance_MultispeedFields> OptionalOS_UnitarySystemPerformance_MultispeedFields ;
#endif

/** \class OS_UnitarySystemPerformance_MultispeedExtensibleFields
 *  \brief Enumeration of OS:UnitarySystemPerformance:Multispeed's Idd and Idf extensible fields
 *  to be used in conjunction with ExtensibleIndex and ExtensibleGroup.
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer ExtensibleIndex.field indices. (The enumeration value names
 *  are more likely to be valid across EnergyPlus and OpenStudio releases, and will break
 *  if they become invalid.)See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_UnitarySystemPerformance_MultispeedExtensibleFields, )
#else
class OS_UnitarySystemPerformance_MultispeedExtensibleFields: public ::EnumBase<OS_UnitarySystemPerformance_MultispeedExtensibleFields> {
 public: 
  enum domain 
  {
HeatingSpeedSupplyAirFlowRatio, CoolingSpeedSupplyAirFlowRatio,   };
  OS_UnitarySystemPerformance_MultispeedExtensibleFields()
   : EnumBase<OS_UnitarySystemPerformance_MultispeedExtensibleFields>(HeatingSpeedSupplyAirFlowRatio) {} 
  OS_UnitarySystemPerformance_MultispeedExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_UnitarySystemPerformance_MultispeedExtensibleFields>(t_name) {} 
  OS_UnitarySystemPerformance_MultispeedExtensibleFields(int t_value) 
   : EnumBase<OS_UnitarySystemPerformance_MultispeedExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_UnitarySystemPerformance_MultispeedExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_UnitarySystemPerformance_MultispeedExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_UnitarySystemPerformance_MultispeedExtensibleFields>;
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
{ OS_UnitarySystemPerformance_MultispeedExtensibleFields::HeatingSpeedSupplyAirFlowRatio, "HeatingSpeedSupplyAirFlowRatio", "Heating Speed Supply Air Flow Ratio"},
{ OS_UnitarySystemPerformance_MultispeedExtensibleFields::CoolingSpeedSupplyAirFlowRatio, "CoolingSpeedSupplyAirFlowRatio", "Cooling Speed Supply Air Flow Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_UnitarySystemPerformance_MultispeedExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_UnitarySystemPerformance_MultispeedExtensibleFields> OptionalOS_UnitarySystemPerformance_MultispeedExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_UNITARYSYSTEMPERFORMANCE_MULTISPEED_FIELDENUMS_HXX
