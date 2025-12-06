/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_MATERIALPROPERTY_GLAZINGSPECTRALDATA_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_MATERIALPROPERTY_GLAZINGSPECTRALDATA_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_MaterialProperty_GlazingSpectralDataFields
 *  \brief Enumeration of OS:MaterialProperty:GlazingSpectralData's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_MaterialProperty_GlazingSpectralDataFields, )
#else
class OS_MaterialProperty_GlazingSpectralDataFields: public ::EnumBase<OS_MaterialProperty_GlazingSpectralDataFields> {
 public: 
  enum domain 
  {
Handle, Name,   };
  OS_MaterialProperty_GlazingSpectralDataFields()
   : EnumBase<OS_MaterialProperty_GlazingSpectralDataFields>(Handle) {} 
  OS_MaterialProperty_GlazingSpectralDataFields(const std::string &t_name) 
   : EnumBase<OS_MaterialProperty_GlazingSpectralDataFields>(t_name) {} 
  OS_MaterialProperty_GlazingSpectralDataFields(int t_value) 
   : EnumBase<OS_MaterialProperty_GlazingSpectralDataFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MaterialProperty_GlazingSpectralDataFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MaterialProperty_GlazingSpectralDataFields>::integer_value()); }
   private:
    friend class EnumBase<OS_MaterialProperty_GlazingSpectralDataFields>;
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
{ OS_MaterialProperty_GlazingSpectralDataFields::Handle, "Handle", "Handle"},
{ OS_MaterialProperty_GlazingSpectralDataFields::Name, "Name", "Name"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MaterialProperty_GlazingSpectralDataFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MaterialProperty_GlazingSpectralDataFields> OptionalOS_MaterialProperty_GlazingSpectralDataFields ;
#endif

/** \class OS_MaterialProperty_GlazingSpectralDataExtensibleFields
 *  \brief Enumeration of OS:MaterialProperty:GlazingSpectralData's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_MaterialProperty_GlazingSpectralDataExtensibleFields, )
#else
class OS_MaterialProperty_GlazingSpectralDataExtensibleFields: public ::EnumBase<OS_MaterialProperty_GlazingSpectralDataExtensibleFields> {
 public: 
  enum domain 
  {
Wavelength, Transmittance, FrontReflectance, BackReflectance,   };
  OS_MaterialProperty_GlazingSpectralDataExtensibleFields()
   : EnumBase<OS_MaterialProperty_GlazingSpectralDataExtensibleFields>(Wavelength) {} 
  OS_MaterialProperty_GlazingSpectralDataExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_MaterialProperty_GlazingSpectralDataExtensibleFields>(t_name) {} 
  OS_MaterialProperty_GlazingSpectralDataExtensibleFields(int t_value) 
   : EnumBase<OS_MaterialProperty_GlazingSpectralDataExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_MaterialProperty_GlazingSpectralDataExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_MaterialProperty_GlazingSpectralDataExtensibleFields>::integer_value()); }
   private:
    friend class EnumBase<OS_MaterialProperty_GlazingSpectralDataExtensibleFields>;
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
{ OS_MaterialProperty_GlazingSpectralDataExtensibleFields::Wavelength, "Wavelength", "Wavelength"},
{ OS_MaterialProperty_GlazingSpectralDataExtensibleFields::Transmittance, "Transmittance", "Transmittance"},
{ OS_MaterialProperty_GlazingSpectralDataExtensibleFields::FrontReflectance, "FrontReflectance", "Front Reflectance"},
{ OS_MaterialProperty_GlazingSpectralDataExtensibleFields::BackReflectance, "BackReflectance", "Back Reflectance"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_MaterialProperty_GlazingSpectralDataExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_MaterialProperty_GlazingSpectralDataExtensibleFields> OptionalOS_MaterialProperty_GlazingSpectralDataExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_MATERIALPROPERTY_GLAZINGSPECTRALDATA_FIELDENUMS_HXX
