/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_DUCTVIEWFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_DUCTVIEWFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class AirflowNetwork_Distribution_DuctViewFactorsFields
 *  \brief Enumeration of AirflowNetwork:Distribution:DuctViewFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(AirflowNetwork_Distribution_DuctViewFactorsFields, )
#else
class AirflowNetwork_Distribution_DuctViewFactorsFields: public ::EnumBase<AirflowNetwork_Distribution_DuctViewFactorsFields> {
 public: 
  enum domain 
  {
LinkageName, DuctSurfaceExposureFraction, DuctSurfaceEmittance,   };
  AirflowNetwork_Distribution_DuctViewFactorsFields()
   : EnumBase<AirflowNetwork_Distribution_DuctViewFactorsFields>(LinkageName) {} 
  AirflowNetwork_Distribution_DuctViewFactorsFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_Distribution_DuctViewFactorsFields>(t_name) {} 
  AirflowNetwork_Distribution_DuctViewFactorsFields(int t_value) 
   : EnumBase<AirflowNetwork_Distribution_DuctViewFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_Distribution_DuctViewFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_Distribution_DuctViewFactorsFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_Distribution_DuctViewFactorsFields>;
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
{ AirflowNetwork_Distribution_DuctViewFactorsFields::LinkageName, "LinkageName", "Linkage Name"},
{ AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceExposureFraction, "DuctSurfaceExposureFraction", "Duct Surface Exposure Fraction"},
{ AirflowNetwork_Distribution_DuctViewFactorsFields::DuctSurfaceEmittance, "DuctSurfaceEmittance", "Duct Surface Emittance"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_Distribution_DuctViewFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_Distribution_DuctViewFactorsFields> OptionalAirflowNetwork_Distribution_DuctViewFactorsFields ;
#endif

/** \class AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields
 *  \brief Enumeration of AirflowNetwork:Distribution:DuctViewFactors's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields, )
#else
class AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields: public ::EnumBase<AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields> {
 public: 
  enum domain 
  {
SurfaceName, SurfaceViewFactor,   };
  AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields()
   : EnumBase<AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields>(SurfaceName) {} 
  AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields(const std::string &t_name) 
   : EnumBase<AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields>(t_name) {} 
  AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields(int t_value) 
   : EnumBase<AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields>;
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
{ AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields::SurfaceName, "SurfaceName", "Surface Name"},
{ AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields::SurfaceViewFactor, "SurfaceViewFactor", "Surface View Factor"},
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
  inline std::ostream &operator<<(std::ostream &os, const AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<AirflowNetwork_Distribution_DuctViewFactorsExtensibleFields> OptionalAirflowNetwork_Distribution_DuctViewFactorsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_AIRFLOWNETWORK_DISTRIBUTION_DUCTVIEWFACTORS_FIELDENUMS_HXX
