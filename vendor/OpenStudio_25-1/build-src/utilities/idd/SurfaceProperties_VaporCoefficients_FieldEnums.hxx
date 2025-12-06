/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_SURFACEPROPERTIES_VAPORCOEFFICIENTS_FIELDENUMS_HXX
#define UTILITIES_IDD_SURFACEPROPERTIES_VAPORCOEFFICIENTS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class SurfaceProperties_VaporCoefficientsFields
 *  \brief Enumeration of SurfaceProperties:VaporCoefficients's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(SurfaceProperties_VaporCoefficientsFields, )
#else
class SurfaceProperties_VaporCoefficientsFields: public ::EnumBase<SurfaceProperties_VaporCoefficientsFields> {
 public: 
  enum domain 
  {
SurfaceName, ConstantExternalVaporTransferCoefficient, ExternalVaporCoefficientValue, ConstantInternalvaporTransferCoefficient, InternalVaporCoefficientValue,   };
  SurfaceProperties_VaporCoefficientsFields()
   : EnumBase<SurfaceProperties_VaporCoefficientsFields>(SurfaceName) {} 
  SurfaceProperties_VaporCoefficientsFields(const std::string &t_name) 
   : EnumBase<SurfaceProperties_VaporCoefficientsFields>(t_name) {} 
  SurfaceProperties_VaporCoefficientsFields(int t_value) 
   : EnumBase<SurfaceProperties_VaporCoefficientsFields>(t_value) {} 
  static std::string enumName() 
  { return "SurfaceProperties_VaporCoefficientsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<SurfaceProperties_VaporCoefficientsFields>::integer_value()); }
   private:
    friend class EnumBase<SurfaceProperties_VaporCoefficientsFields>;
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
{ SurfaceProperties_VaporCoefficientsFields::SurfaceName, "SurfaceName", "Surface Name"},
{ SurfaceProperties_VaporCoefficientsFields::ConstantExternalVaporTransferCoefficient, "ConstantExternalVaporTransferCoefficient", "Constant External Vapor Transfer Coefficient"},
{ SurfaceProperties_VaporCoefficientsFields::ExternalVaporCoefficientValue, "ExternalVaporCoefficientValue", "External Vapor Coefficient Value"},
{ SurfaceProperties_VaporCoefficientsFields::ConstantInternalvaporTransferCoefficient, "ConstantInternalvaporTransferCoefficient", "Constant Internal vapor Transfer Coefficient"},
{ SurfaceProperties_VaporCoefficientsFields::InternalVaporCoefficientValue, "InternalVaporCoefficientValue", "Internal Vapor Coefficient Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const SurfaceProperties_VaporCoefficientsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<SurfaceProperties_VaporCoefficientsFields> OptionalSurfaceProperties_VaporCoefficientsFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_SURFACEPROPERTIES_VAPORCOEFFICIENTS_FIELDENUMS_HXX
