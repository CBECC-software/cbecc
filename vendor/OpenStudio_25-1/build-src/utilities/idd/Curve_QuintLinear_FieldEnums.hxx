/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) Alliance for Sustainable Energy, LLC.
*  See also https://openstudio.net/license
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CURVE_QUINTLINEAR_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_QUINTLINEAR_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_QuintLinearFields
 *  \brief Enumeration of Curve:QuintLinear's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_QuintLinearFields, )
#else
class Curve_QuintLinearFields: public ::EnumBase<Curve_QuintLinearFields> {
 public: 
  enum domain 
  {
Name, Coefficient1Constant, Coefficient2v, Coefficient3w, Coefficient4x, Coefficient5y, Coefficient6z, MinimumValueofv, MaximumValueofv, MinimumValueofw, MaximumValueofw, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumValueofz, MaximumValueofz, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforv, InputUnitTypeforw, InputUnitTypeforx, InputUnitTypefory, InputUnitTypeforz,   };
  Curve_QuintLinearFields()
   : EnumBase<Curve_QuintLinearFields>(Name) {} 
  Curve_QuintLinearFields(const std::string &t_name) 
   : EnumBase<Curve_QuintLinearFields>(t_name) {} 
  Curve_QuintLinearFields(int t_value) 
   : EnumBase<Curve_QuintLinearFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_QuintLinearFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_QuintLinearFields>::integer_value()); }
   private:
    friend class EnumBase<Curve_QuintLinearFields>;
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
{ Curve_QuintLinearFields::Name, "Name", "Name"},
{ Curve_QuintLinearFields::Coefficient1Constant, "Coefficient1Constant", "Coefficient1 Constant"},
{ Curve_QuintLinearFields::Coefficient2v, "Coefficient2v", "Coefficient2 v"},
{ Curve_QuintLinearFields::Coefficient3w, "Coefficient3w", "Coefficient3 w"},
{ Curve_QuintLinearFields::Coefficient4x, "Coefficient4x", "Coefficient4 x"},
{ Curve_QuintLinearFields::Coefficient5y, "Coefficient5y", "Coefficient5 y"},
{ Curve_QuintLinearFields::Coefficient6z, "Coefficient6z", "Coefficient6 z"},
{ Curve_QuintLinearFields::MinimumValueofv, "MinimumValueofv", "Minimum Value of v"},
{ Curve_QuintLinearFields::MaximumValueofv, "MaximumValueofv", "Maximum Value of v"},
{ Curve_QuintLinearFields::MinimumValueofw, "MinimumValueofw", "Minimum Value of w"},
{ Curve_QuintLinearFields::MaximumValueofw, "MaximumValueofw", "Maximum Value of w"},
{ Curve_QuintLinearFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ Curve_QuintLinearFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ Curve_QuintLinearFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ Curve_QuintLinearFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ Curve_QuintLinearFields::MinimumValueofz, "MinimumValueofz", "Minimum Value of z"},
{ Curve_QuintLinearFields::MaximumValueofz, "MaximumValueofz", "Maximum Value of z"},
{ Curve_QuintLinearFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ Curve_QuintLinearFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ Curve_QuintLinearFields::InputUnitTypeforv, "InputUnitTypeforv", "Input Unit Type for v"},
{ Curve_QuintLinearFields::InputUnitTypeforw, "InputUnitTypeforw", "Input Unit Type for w"},
{ Curve_QuintLinearFields::InputUnitTypeforx, "InputUnitTypeforx", "Input Unit Type for x"},
{ Curve_QuintLinearFields::InputUnitTypefory, "InputUnitTypefory", "Input Unit Type for y"},
{ Curve_QuintLinearFields::InputUnitTypeforz, "InputUnitTypeforz", "Input Unit Type for z"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_QuintLinearFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_QuintLinearFields> OptionalCurve_QuintLinearFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_QUINTLINEAR_FIELDENUMS_HXX
