/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_ENERGYMANAGEMENTSYSTEM_PROGRAM_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_ENERGYMANAGEMENTSYSTEM_PROGRAM_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_EnergyManagementSystem_ProgramFields
 *  \brief Enumeration of OS:EnergyManagementSystem:Program's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_EnergyManagementSystem_ProgramFields, )
#else
class OS_EnergyManagementSystem_ProgramFields: public ::EnumBase<OS_EnergyManagementSystem_ProgramFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_EnergyManagementSystem_ProgramFields()
   : EnumBase<OS_EnergyManagementSystem_ProgramFields>(Handle) {} 
  OS_EnergyManagementSystem_ProgramFields(const std::string &t_name) 
   : EnumBase<OS_EnergyManagementSystem_ProgramFields>(t_name) {} 
  OS_EnergyManagementSystem_ProgramFields(int t_value) 
   : EnumBase<OS_EnergyManagementSystem_ProgramFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_EnergyManagementSystem_ProgramFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_EnergyManagementSystem_ProgramFields>::integer_value()); }
   private:
    friend class EnumBase<OS_EnergyManagementSystem_ProgramFields>;
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
{ OS_EnergyManagementSystem_ProgramFields::Handle, "Handle", "Handle"},
{ OS_EnergyManagementSystem_ProgramFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_EnergyManagementSystem_ProgramFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_EnergyManagementSystem_ProgramFields> OptionalOS_EnergyManagementSystem_ProgramFields ;
#endif

/** \class OS_EnergyManagementSystem_ProgramExtensibleFields
 *  \brief Enumeration of OS:EnergyManagementSystem:Program's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_EnergyManagementSystem_ProgramExtensibleFields, )
#else
class OS_EnergyManagementSystem_ProgramExtensibleFields: public ::EnumBase<OS_EnergyManagementSystem_ProgramExtensibleFields> {
 public: 
  enum domain 
  {
ProgramLine,   };
  OS_EnergyManagementSystem_ProgramExtensibleFields()
   : EnumBase<OS_EnergyManagementSystem_ProgramExtensibleFields>(ProgramLine) {} 
  OS_EnergyManagementSystem_ProgramExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_EnergyManagementSystem_ProgramExtensibleFields>(t_name) {} 
  OS_EnergyManagementSystem_ProgramExtensibleFields(int t_value) 
   : EnumBase<OS_EnergyManagementSystem_ProgramExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_EnergyManagementSystem_ProgramExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_EnergyManagementSystem_ProgramExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_EnergyManagementSystem_ProgramExtensibleFields>;
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
{ OS_EnergyManagementSystem_ProgramExtensibleFields::ProgramLine, "ProgramLine", "Program Line"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_EnergyManagementSystem_ProgramExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_EnergyManagementSystem_ProgramExtensibleFields> OptionalOS_EnergyManagementSystem_ProgramExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_ENERGYMANAGEMENTSYSTEM_PROGRAM_FIELDENUMS_HXX
