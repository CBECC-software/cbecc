/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_BRANCH_FIELDENUMS_HXX
#define UTILITIES_IDD_BRANCH_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class BranchFields
 *  \brief Enumeration of Branch's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(BranchFields, )
#else
class BranchFields: public ::EnumBase<BranchFields> {
 public: 
  enum domain 
  {
Name, PressureDropCurveName,   };
  BranchFields()
   : EnumBase<BranchFields>(Name) {} 
  BranchFields(const std::string &t_name) 
   : EnumBase<BranchFields>(t_name) {} 
  BranchFields(int t_value) 
   : EnumBase<BranchFields>(t_value) {} 
  static std::string enumName() 
  { return "BranchFields"; }
  domain value() const { return static_cast<domain>(EnumBase<BranchFields>::integer_value()); }
   private:
    friend class EnumBase<BranchFields>;
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
{ BranchFields::Name, "Name", "Name"},
{ BranchFields::PressureDropCurveName, "PressureDropCurveName", "Pressure Drop Curve Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const BranchFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<BranchFields> OptionalBranchFields ;
#endif

/** \class BranchExtensibleFields
 *  \brief Enumeration of Branch's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(BranchExtensibleFields, )
#else
class BranchExtensibleFields: public ::EnumBase<BranchExtensibleFields> {
 public: 
  enum domain 
  {
ComponentObjectType, ComponentName, ComponentInletNodeName, ComponentOutletNodeName,   };
  BranchExtensibleFields()
   : EnumBase<BranchExtensibleFields>(ComponentObjectType) {} 
  BranchExtensibleFields(const std::string &t_name) 
   : EnumBase<BranchExtensibleFields>(t_name) {} 
  BranchExtensibleFields(int t_value) 
   : EnumBase<BranchExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "BranchExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<BranchExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<BranchExtensibleFields>;
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
{ BranchExtensibleFields::ComponentObjectType, "ComponentObjectType", "Component Object Type"},
{ BranchExtensibleFields::ComponentName, "ComponentName", "Component Name"},
{ BranchExtensibleFields::ComponentInletNodeName, "ComponentInletNodeName", "Component Inlet Node Name"},
{ BranchExtensibleFields::ComponentOutletNodeName, "ComponentOutletNodeName", "Component Outlet Node Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const BranchExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<BranchExtensibleFields> OptionalBranchExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_BRANCH_FIELDENUMS_HXX
