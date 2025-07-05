/***********************************************************************************************************************
*  OpenStudio(R), Copyright (c) 2008-2023, Alliance for Sustainable Energy, LLC, and other contributors. All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
*  following conditions are met:
*
*  (1) Redistributions of source code must retain the above copyright notice, this list of conditions and the following
*  disclaimer.
*
*  (2) Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
*  disclaimer in the documentation and/or other materials provided with the distribution.
*
*  (3) Neither the name of the copyright holder nor the names of any contributors may be used to endorse or promote products
*  derived from this software without specific prior written permission from the respective party.
*
*  (4) Other than as required in clauses (1) and (2), distributions in any form of modifications or other derivative works
*  may not use the "OpenStudio" trademark, "OS", "os", or any other confusingly similar designation without specific prior
*  written permission from Alliance for Sustainable Energy, LLC.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER(S) AND ANY CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
*  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
*  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER(S), ANY CONTRIBUTORS, THE UNITED STATES GOVERNMENT, OR THE UNITED
*  STATES DEPARTMENT OF ENERGY, NOR ANY OF THEIR EMPLOYEES, BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
*  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
*  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
*  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***********************************************************************************************************************/

#ifndef UTILITIES_IDD_CURVE_CHILLERPARTLOADWITHLIFT_FIELDENUMS_HXX
#define UTILITIES_IDD_CURVE_CHILLERPARTLOADWITHLIFT_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Curve_ChillerPartLoadWithLiftFields
 *  \brief Enumeration of Curve:ChillerPartLoadWithLift's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Curve_ChillerPartLoadWithLiftFields, )
#else
class Curve_ChillerPartLoadWithLiftFields: public ::EnumBase<Curve_ChillerPartLoadWithLiftFields> {
 public: 
  enum domain 
  {
Name, Coefficient1C1, Coefficient2C2, Coefficient3C3, Coefficient4C4, Coefficient5C5, Coefficient6C6, Coefficient7C7, Coefficient8C8, Coefficient9C9, Coefficient10C10, Coefficient11C11, Coefficient12C12, MinimumValueofx, MaximumValueofx, MinimumValueofy, MaximumValueofy, MinimumValueofz, MaximumValueofz, MinimumCurveOutput, MaximumCurveOutput, InputUnitTypeforx, InputUnitTypefory, InputUnitTypeforz, OutputUnitType,   };
  Curve_ChillerPartLoadWithLiftFields()
   : EnumBase<Curve_ChillerPartLoadWithLiftFields>(Name) {} 
  Curve_ChillerPartLoadWithLiftFields(const std::string &t_name) 
   : EnumBase<Curve_ChillerPartLoadWithLiftFields>(t_name) {} 
  Curve_ChillerPartLoadWithLiftFields(int t_value) 
   : EnumBase<Curve_ChillerPartLoadWithLiftFields>(t_value) {} 
  static std::string enumName() 
  { return "Curve_ChillerPartLoadWithLiftFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Curve_ChillerPartLoadWithLiftFields>::value()); }
   private:
    friend class EnumBase<Curve_ChillerPartLoadWithLiftFields>;
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
{ Curve_ChillerPartLoadWithLiftFields::Name, "Name", "Name"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient1C1, "Coefficient1C1", "Coefficient1 C1"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient2C2, "Coefficient2C2", "Coefficient2 C2"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient3C3, "Coefficient3C3", "Coefficient3 C3"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient4C4, "Coefficient4C4", "Coefficient4 C4"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient5C5, "Coefficient5C5", "Coefficient5 C5"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient6C6, "Coefficient6C6", "Coefficient6 C6"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient7C7, "Coefficient7C7", "Coefficient7 C7"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient8C8, "Coefficient8C8", "Coefficient8 C8"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient9C9, "Coefficient9C9", "Coefficient9 C9"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient10C10, "Coefficient10C10", "Coefficient10 C10"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient11C11, "Coefficient11C11", "Coefficient11 C11"},
{ Curve_ChillerPartLoadWithLiftFields::Coefficient12C12, "Coefficient12C12", "Coefficient12 C12"},
{ Curve_ChillerPartLoadWithLiftFields::MinimumValueofx, "MinimumValueofx", "Minimum Value of x"},
{ Curve_ChillerPartLoadWithLiftFields::MaximumValueofx, "MaximumValueofx", "Maximum Value of x"},
{ Curve_ChillerPartLoadWithLiftFields::MinimumValueofy, "MinimumValueofy", "Minimum Value of y"},
{ Curve_ChillerPartLoadWithLiftFields::MaximumValueofy, "MaximumValueofy", "Maximum Value of y"},
{ Curve_ChillerPartLoadWithLiftFields::MinimumValueofz, "MinimumValueofz", "Minimum Value of z"},
{ Curve_ChillerPartLoadWithLiftFields::MaximumValueofz, "MaximumValueofz", "Maximum Value of z"},
{ Curve_ChillerPartLoadWithLiftFields::MinimumCurveOutput, "MinimumCurveOutput", "Minimum Curve Output"},
{ Curve_ChillerPartLoadWithLiftFields::MaximumCurveOutput, "MaximumCurveOutput", "Maximum Curve Output"},
{ Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforx, "InputUnitTypeforx", "Input Unit Type for x"},
{ Curve_ChillerPartLoadWithLiftFields::InputUnitTypefory, "InputUnitTypefory", "Input Unit Type for y"},
{ Curve_ChillerPartLoadWithLiftFields::InputUnitTypeforz, "InputUnitTypeforz", "Input Unit Type for z"},
{ Curve_ChillerPartLoadWithLiftFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
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
  inline std::ostream &operator<<(std::ostream &os, const Curve_ChillerPartLoadWithLiftFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Curve_ChillerPartLoadWithLiftFields> OptionalCurve_ChillerPartLoadWithLiftFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_CURVE_CHILLERPARTLOADWITHLIFT_FIELDENUMS_HXX
