/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_COIL_HEATING_ELECTRIC_MULTISTAGE_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_COIL_HEATING_ELECTRIC_MULTISTAGE_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Coil_Heating_Electric_MultiStageFields
 *  \brief Enumeration of OS:Coil:Heating:Electric:MultiStage's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Coil_Heating_Electric_MultiStageFields, )
#else
class OS_Coil_Heating_Electric_MultiStageFields: public ::EnumBase<OS_Coil_Heating_Electric_MultiStageFields> {
 public: 
  enum domain 
  {
Handle, Name, AvailabilitySchedule, AirInletNode, AirOutletNode,   };
  OS_Coil_Heating_Electric_MultiStageFields()
   : EnumBase<OS_Coil_Heating_Electric_MultiStageFields>(Handle) {} 
  OS_Coil_Heating_Electric_MultiStageFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_Electric_MultiStageFields>(t_name) {} 
  OS_Coil_Heating_Electric_MultiStageFields(int t_value) 
   : EnumBase<OS_Coil_Heating_Electric_MultiStageFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_Electric_MultiStageFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_Electric_MultiStageFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_Electric_MultiStageFields>;
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
{ OS_Coil_Heating_Electric_MultiStageFields::Handle, "Handle", "Handle"},
{ OS_Coil_Heating_Electric_MultiStageFields::Name, "Name", "Name"},
{ OS_Coil_Heating_Electric_MultiStageFields::AvailabilitySchedule, "AvailabilitySchedule", "Availability Schedule"},
{ OS_Coil_Heating_Electric_MultiStageFields::AirInletNode, "AirInletNode", "Air Inlet Node"},
{ OS_Coil_Heating_Electric_MultiStageFields::AirOutletNode, "AirOutletNode", "Air Outlet Node"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_Electric_MultiStageFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_Electric_MultiStageFields> OptionalOS_Coil_Heating_Electric_MultiStageFields ;
#endif

/** \class OS_Coil_Heating_Electric_MultiStageExtensibleFields
 *  \brief Enumeration of OS:Coil:Heating:Electric:MultiStage's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Coil_Heating_Electric_MultiStageExtensibleFields, )
#else
class OS_Coil_Heating_Electric_MultiStageExtensibleFields: public ::EnumBase<OS_Coil_Heating_Electric_MultiStageExtensibleFields> {
 public: 
  enum domain 
  {
Stage,   };
  OS_Coil_Heating_Electric_MultiStageExtensibleFields()
   : EnumBase<OS_Coil_Heating_Electric_MultiStageExtensibleFields>(Stage) {} 
  OS_Coil_Heating_Electric_MultiStageExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Coil_Heating_Electric_MultiStageExtensibleFields>(t_name) {} 
  OS_Coil_Heating_Electric_MultiStageExtensibleFields(int t_value) 
   : EnumBase<OS_Coil_Heating_Electric_MultiStageExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Coil_Heating_Electric_MultiStageExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Coil_Heating_Electric_MultiStageExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Coil_Heating_Electric_MultiStageExtensibleFields>;
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
{ OS_Coil_Heating_Electric_MultiStageExtensibleFields::Stage, "Stage", "Stage"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Coil_Heating_Electric_MultiStageExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Coil_Heating_Electric_MultiStageExtensibleFields> OptionalOS_Coil_Heating_Electric_MultiStageExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_COIL_HEATING_ELECTRIC_MULTISTAGE_FIELDENUMS_HXX
