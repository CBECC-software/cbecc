/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_FLUIDPROPERTIES_GLYCOLCONCENTRATION_FIELDENUMS_HXX
#define UTILITIES_IDD_FLUIDPROPERTIES_GLYCOLCONCENTRATION_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class FluidProperties_GlycolConcentrationFields
 *  \brief Enumeration of FluidProperties:GlycolConcentration's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(FluidProperties_GlycolConcentrationFields, )
#else
class FluidProperties_GlycolConcentrationFields: public ::EnumBase<FluidProperties_GlycolConcentrationFields> {
 public: 
  enum domain 
  {
Name, GlycolType, UserDefinedGlycolName, GlycolConcentration,   };
  FluidProperties_GlycolConcentrationFields()
   : EnumBase<FluidProperties_GlycolConcentrationFields>(Name) {} 
  FluidProperties_GlycolConcentrationFields(const std::string &t_name) 
   : EnumBase<FluidProperties_GlycolConcentrationFields>(t_name) {} 
  FluidProperties_GlycolConcentrationFields(int t_value) 
   : EnumBase<FluidProperties_GlycolConcentrationFields>(t_value) {} 
  static std::string enumName() 
  { return "FluidProperties_GlycolConcentrationFields"; }
  domain value() const { return static_cast<domain>(EnumBase<FluidProperties_GlycolConcentrationFields>::integer_value()); }
   private:
    friend class EnumBase<FluidProperties_GlycolConcentrationFields>;
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
{ FluidProperties_GlycolConcentrationFields::Name, "Name", "Name"},
{ FluidProperties_GlycolConcentrationFields::GlycolType, "GlycolType", "Glycol Type"},
{ FluidProperties_GlycolConcentrationFields::UserDefinedGlycolName, "UserDefinedGlycolName", "User Defined Glycol Name"},
{ FluidProperties_GlycolConcentrationFields::GlycolConcentration, "GlycolConcentration", "Glycol Concentration"},
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
  inline std::ostream &operator<<(std::ostream &os, const FluidProperties_GlycolConcentrationFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<FluidProperties_GlycolConcentrationFields> OptionalFluidProperties_GlycolConcentrationFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_FLUIDPROPERTIES_GLYCOLCONCENTRATION_FIELDENUMS_HXX
