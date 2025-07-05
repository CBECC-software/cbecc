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

#ifndef UTILITIES_IDD_OS_TABLE_MULTIVARIABLELOOKUP_FIELDENUMS_HXX
#define UTILITIES_IDD_OS_TABLE_MULTIVARIABLELOOKUP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class OS_Table_MultiVariableLookupFields
 *  \brief Enumeration of OS:Table:MultiVariableLookup's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(OS_Table_MultiVariableLookupFields, )
#else
class OS_Table_MultiVariableLookupFields: public ::EnumBase<OS_Table_MultiVariableLookupFields> {
 public: 
  enum domain 
  {
Handle, Name, InterpolationMethod, NumberofInterpolationPoints, CurveType, TableDataFormat, ExternalFileName, X1SortOrder, X2SortOrder, NormalizationReference, MinimumValueofX1, MaximumValueofX1, MinimumValueofX2, MaximumValueofX2, MinimumValueofX3, MaximumValueofX3, MinimumValueofX4, MaximumValueofX4, MinimumValueofX5, MaximumValueofX5, MinimumTableOutput, MaximumTableOutput, InputUnitTypeforX1, InputUnitTypeforX2, InputUnitTypeforX3, InputUnitTypeforX4, InputUnitTypeforX5, OutputUnitType, NumberofIndependentVariables,   };
  OS_Table_MultiVariableLookupFields()
   : EnumBase<OS_Table_MultiVariableLookupFields>(Handle) {} 
  OS_Table_MultiVariableLookupFields(const std::string &t_name) 
   : EnumBase<OS_Table_MultiVariableLookupFields>(t_name) {} 
  OS_Table_MultiVariableLookupFields(int t_value) 
   : EnumBase<OS_Table_MultiVariableLookupFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Table_MultiVariableLookupFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Table_MultiVariableLookupFields>::value()); }
   private:
    friend class EnumBase<OS_Table_MultiVariableLookupFields>;
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
{ OS_Table_MultiVariableLookupFields::Handle, "Handle", "Handle"},
{ OS_Table_MultiVariableLookupFields::Name, "Name", "Name"},
{ OS_Table_MultiVariableLookupFields::InterpolationMethod, "InterpolationMethod", "Interpolation Method"},
{ OS_Table_MultiVariableLookupFields::NumberofInterpolationPoints, "NumberofInterpolationPoints", "Number of Interpolation Points"},
{ OS_Table_MultiVariableLookupFields::CurveType, "CurveType", "Curve Type"},
{ OS_Table_MultiVariableLookupFields::TableDataFormat, "TableDataFormat", "Table Data Format"},
{ OS_Table_MultiVariableLookupFields::ExternalFileName, "ExternalFileName", "External File Name"},
{ OS_Table_MultiVariableLookupFields::X1SortOrder, "X1SortOrder", "X1 Sort Order"},
{ OS_Table_MultiVariableLookupFields::X2SortOrder, "X2SortOrder", "X2 Sort Order"},
{ OS_Table_MultiVariableLookupFields::NormalizationReference, "NormalizationReference", "Normalization Reference"},
{ OS_Table_MultiVariableLookupFields::MinimumValueofX1, "MinimumValueofX1", "Minimum Value of X1"},
{ OS_Table_MultiVariableLookupFields::MaximumValueofX1, "MaximumValueofX1", "Maximum Value of X1"},
{ OS_Table_MultiVariableLookupFields::MinimumValueofX2, "MinimumValueofX2", "Minimum Value of X2"},
{ OS_Table_MultiVariableLookupFields::MaximumValueofX2, "MaximumValueofX2", "Maximum Value of X2"},
{ OS_Table_MultiVariableLookupFields::MinimumValueofX3, "MinimumValueofX3", "Minimum Value of X3"},
{ OS_Table_MultiVariableLookupFields::MaximumValueofX3, "MaximumValueofX3", "Maximum Value of X3"},
{ OS_Table_MultiVariableLookupFields::MinimumValueofX4, "MinimumValueofX4", "Minimum Value of X4"},
{ OS_Table_MultiVariableLookupFields::MaximumValueofX4, "MaximumValueofX4", "Maximum Value of X4"},
{ OS_Table_MultiVariableLookupFields::MinimumValueofX5, "MinimumValueofX5", "Minimum Value of X5"},
{ OS_Table_MultiVariableLookupFields::MaximumValueofX5, "MaximumValueofX5", "Maximum Value of X5"},
{ OS_Table_MultiVariableLookupFields::MinimumTableOutput, "MinimumTableOutput", "Minimum Table Output"},
{ OS_Table_MultiVariableLookupFields::MaximumTableOutput, "MaximumTableOutput", "Maximum Table Output"},
{ OS_Table_MultiVariableLookupFields::InputUnitTypeforX1, "InputUnitTypeforX1", "Input Unit Type for X1"},
{ OS_Table_MultiVariableLookupFields::InputUnitTypeforX2, "InputUnitTypeforX2", "Input Unit Type for X2"},
{ OS_Table_MultiVariableLookupFields::InputUnitTypeforX3, "InputUnitTypeforX3", "Input Unit Type for X3"},
{ OS_Table_MultiVariableLookupFields::InputUnitTypeforX4, "InputUnitTypeforX4", "Input Unit Type for X4"},
{ OS_Table_MultiVariableLookupFields::InputUnitTypeforX5, "InputUnitTypeforX5", "Input Unit Type for X5"},
{ OS_Table_MultiVariableLookupFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
{ OS_Table_MultiVariableLookupFields::NumberofIndependentVariables, "NumberofIndependentVariables", "Number of Independent Variables"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Table_MultiVariableLookupFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Table_MultiVariableLookupFields> OptionalOS_Table_MultiVariableLookupFields ;
#endif

/** \class OS_Table_MultiVariableLookupExtensibleFields
 *  \brief Enumeration of OS:Table:MultiVariableLookup's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(OS_Table_MultiVariableLookupExtensibleFields, )
#else
class OS_Table_MultiVariableLookupExtensibleFields: public ::EnumBase<OS_Table_MultiVariableLookupExtensibleFields> {
 public: 
  enum domain 
  {
Data,   };
  OS_Table_MultiVariableLookupExtensibleFields()
   : EnumBase<OS_Table_MultiVariableLookupExtensibleFields>(Data) {} 
  OS_Table_MultiVariableLookupExtensibleFields(const std::string &t_name) 
   : EnumBase<OS_Table_MultiVariableLookupExtensibleFields>(t_name) {} 
  OS_Table_MultiVariableLookupExtensibleFields(int t_value) 
   : EnumBase<OS_Table_MultiVariableLookupExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "OS_Table_MultiVariableLookupExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<OS_Table_MultiVariableLookupExtensibleFields>::value()); }
   private:
    friend class EnumBase<OS_Table_MultiVariableLookupExtensibleFields>;
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
{ OS_Table_MultiVariableLookupExtensibleFields::Data, "Data", "Data"},
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
  inline std::ostream &operator<<(std::ostream &os, const OS_Table_MultiVariableLookupExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<OS_Table_MultiVariableLookupExtensibleFields> OptionalOS_Table_MultiVariableLookupExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_OS_TABLE_MULTIVARIABLELOOKUP_FIELDENUMS_HXX
