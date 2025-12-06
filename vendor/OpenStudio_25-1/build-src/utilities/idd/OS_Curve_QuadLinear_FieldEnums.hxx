/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_OS_CURVE_QUADLINEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_CURVE_QUADLINEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Curve_QuadLinearFields
 *  \brief Enumeration of OS:Curve:QuadLinear's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Curve_QuadLinearFields, )
#else
class OS_Curve_QuadLinearFields: public ::EnumBase<OS_Curve_QuadLinearFields> {
 public: 
  enum domain 
  {
Handle, Name, Coefficient1Constant, Coefficient2w, Coefficient3x, Coefficient4y, Coefficient5z, MinimumValueofw, MaximumValueofw, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumValueofz, MaximumValueofz, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforw, InputUnitTypeforx, InputUnitTypefory, InputUnitTypeforz,   };
  OS_Curve_QuadLinearFields()
   : EnumBase<OS_Curve_QuadLinearFields>(Handle) {} 
  OS_Curve_QuadLinearFields(const std::string &t_name) 
   : EnumBase<OS_Curve_QuadLinearFields>(t_name) {} 
  OS_Curve_QuadLinearFields(int t_value) 
   : EnumBase<OS_Curve_QuadLinearFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Curve_QuadLinearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Curve_QuadLinearFields>::integer_value()); }
   private:
    friend class EnumBase<OS_Curve_QuadLinearFields>;
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
{ OS_Curve_QuadLinearFields::Handle, "Handle", "Handle"},
{ OS_Curve_QuadLinearFields::Name, "Name", "Name"},
{ OS_Curve_QuadLinearFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ OS_Curve_QuadLinearFields::Coefficient2w, "Coefficient2w", "Coefficient2 w"},
{ OS_Curve_QuadLinearFields::Coefficient3x, "Coefficient3x", "Coefficient3 x"},
{ OS_Curve_QuadLinearFields::Coefficient4y, "Coefficient4y", "Coefficient4 y"},
{ OS_Curve_QuadLinearFields::Coefficient5z, "Coefficient5z", "Coefficient5 z"},
{ OS_Curve_QuadLinearFields::MinimumValueofw, "MinimumValueofw", "Minimum Value of w"},
{ OS_Curve_QuadLinearFields::MaximumValueofw, "MaximumValueofw", "Maximum Value of w"},
{ OS_Curve_QuadLinearFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ OS_Curve_QuadLinearFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ OS_Curve_QuadLinearFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ OS_Curve_QuadLinearFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ OS_Curve_QuadLinearFields::MinimumValueofz, "MinimumValueofz", "Minimum Value of z"},
{ OS_Curve_QuadLinearFields::MaximumValueofz, "MaximumValueofz", "Maximum Value of z"},
{ OS_Curve_QuadLinearFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ OS_Curve_QuadLinearFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ OS_Curve_QuadLinearFields::InputUnitTypeforw, "InputUnitTypeforw", "Input Unit Type for w"},
{ OS_Curve_QuadLinearFields::InputUnitTypeforx, "InputUnitTypeforx", "Input Unit Type for x"},
{ OS_Curve_QuadLinearFields::InputUnitTypefory, "InputUnitTypefory", "Input Unit Type for y"},
{ OS_Curve_QuadLinearFields::InputUnitTypeforz, "InputUnitTypeforz", "Input Unit Type for z"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Curve_QuadLinearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Curve_QuadLinearFields> OptionalOS_Curve_QuadLinearFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_CURVE_QUADLINEAR_FIELDENUMS_HXX
