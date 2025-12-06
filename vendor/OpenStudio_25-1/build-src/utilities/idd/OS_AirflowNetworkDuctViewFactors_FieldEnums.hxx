/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_AIRFLOWNETWORKDUCTVIEWFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_AIRFLOWNETWORKDUCTVIEWFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_AirflowNetworkDuctViewFactorsFields
 *  \brief Enumeration of OS:AirflowNetworkDuctViewFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_AirflowNetworkDuctViewFactorsFields, )
#else
class OS_AirflowNetworkDuctViewFactorsFields: public ::EnumBase<OS_AirflowNetworkDuctViewFactorsFields> {
 public: 
  enum domain 
  {
Handle, LinkageName, DuctSurfaceExposureFraction, DuctSurfaceEmittance,   };
  OS_AirflowNetworkDuctViewFactorsFields()
   : EnumBase<OS_AirflowNetworkDuctViewFactorsFields>(Handle) {} 
  OS_AirflowNetworkDuctViewFactorsFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkDuctViewFactorsFields>(t_name) {} 
  OS_AirflowNetworkDuctViewFactorsFields(int t_value) 
   : EnumBase<OS_AirflowNetworkDuctViewFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkDuctViewFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkDuctViewFactorsFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkDuctViewFactorsFields>;
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
{ OS_AirflowNetworkDuctViewFactorsFields::Handle, "Handle", "Handle"},
{ OS_AirflowNetworkDuctViewFactorsFields::LinkageName, "LinkageName", "Linkage Name"},
{ OS_AirflowNetworkDuctViewFactorsFields::DuctSurfaceExposureFraction, "DuctSurfaceExposureFraction", "Duct Surface Exposure Fraction"},
{ OS_AirflowNetworkDuctViewFactorsFields::DuctSurfaceEmittance, "DuctSurfaceEmittance", "Duct Surface Emittance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkDuctViewFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkDuctViewFactorsFields> OptionalOS_AirflowNetworkDuctViewFactorsFields ;
#endif

/** \class OS_AirflowNetworkDuctViewFactorsExtensibleFields
 *  \brief Enumeration of OS:AirflowNetworkDuctViewFactors's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_AirflowNetworkDuctViewFactorsExtensibleFields, )
#else
class OS_AirflowNetworkDuctViewFactorsExtensibleFields: public ::EnumBase<OS_AirflowNetworkDuctViewFactorsExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, SurfaceViewFactor,   };
  OS_AirflowNetworkDuctViewFactorsExtensibleFields()
   : EnumBase<OS_AirflowNetworkDuctViewFactorsExtensibleFields>(SurfaceName) {} 
  OS_AirflowNetworkDuctViewFactorsExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_AirflowNetworkDuctViewFactorsExtensibleFields>(t_name) {} 
  OS_AirflowNetworkDuctViewFactorsExtensibleFields(int t_value) 
   : EnumBase<OS_AirflowNetworkDuctViewFactorsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_AirflowNetworkDuctViewFactorsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_AirflowNetworkDuctViewFactorsExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_AirflowNetworkDuctViewFactorsExtensibleFields>;
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
{ OS_AirflowNetworkDuctViewFactorsExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ OS_AirflowNetworkDuctViewFactorsExtensibleFields::SurfaceViewFactor, "SurfaceViewFactor", "Surface View Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_AirflowNetworkDuctViewFactorsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_AirflowNetworkDuctViewFactorsExtensibleFields> OptionalOS_AirflowNetworkDuctViewFactorsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_AIRFLOWNETWORKDUCTVIEWFACTORS_FIELDENUMS_HXX
