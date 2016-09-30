/**********************************************************************
*  Copyright (c) 2008-2016, Alliance for Sustainable Energy.
*  All rights reserved.
*
*  This library is free software; you can redistribute it and/or
*  modify it under the terms of the GNU Lesser General Public
*  License as published by the Free Software Foundation; either
*  version 2.1 of the License, or (at your option) any later version.
*
*  This library is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
*  Lesser General Public License for more details.
*
*  You should have received a copy of the GNU Lesser General Public
*  License along with this library; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
**********************************************************************/

#ifndef UTILITIES_IDD_TABLE_MULTIVARIABLELOOKUP_FIELDENUMS_HXX
#define UTILITIES_IDD_TABLE_MULTIVARIABLELOOKUP_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class Table_MultiVariableLookupFields
 *  \brief Enumeration of Table:MultiVariableLookup's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(Table_MultiVariableLookupFields, )
#else
class Table_MultiVariableLookupFields: public ::EnumBase<Table_MultiVariableLookupFields> {
 public: 
  enum domain 
  {
Name, InterpolationMethod, NumberofInterpolationPoints, CurveType, TableDataFormat, ExternalFileName, X1SortOrder, X2SortOrder, NormalizationReference, MinimumValueofX1, MaximumValueofX1, MinimumValueofX2, MaximumValueofX2, MinimumValueofX3, MaximumValueofX3, MinimumValueofX4, MaximumValueofX4, MinimumValueofX5, MaximumValueofX5, MinimumTableOutput, MaximumTableOutput, InputUnitTypeforX1, InputUnitTypeforX2, InputUnitTypeforX3, InputUnitTypeforX4, InputUnitTypeforX5, OutputUnitType, NumberofIndependentVariables,   };
  Table_MultiVariableLookupFields()
   : EnumBase<Table_MultiVariableLookupFields>(Name) {} 
  Table_MultiVariableLookupFields(const std::string &t_name) 
   : EnumBase<Table_MultiVariableLookupFields>(t_name) {} 
  Table_MultiVariableLookupFields(int t_value) 
   : EnumBase<Table_MultiVariableLookupFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_MultiVariableLookupFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_MultiVariableLookupFields>::value()); }
   private:
    friend class EnumBase<Table_MultiVariableLookupFields>;
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
{ Table_MultiVariableLookupFields::Name, "Name", "Name"},
{ Table_MultiVariableLookupFields::InterpolationMethod, "InterpolationMethod", "Interpolation Method"},
{ Table_MultiVariableLookupFields::NumberofInterpolationPoints, "NumberofInterpolationPoints", "Number of Interpolation Points"},
{ Table_MultiVariableLookupFields::CurveType, "CurveType", "Curve Type"},
{ Table_MultiVariableLookupFields::TableDataFormat, "TableDataFormat", "Table Data Format"},
{ Table_MultiVariableLookupFields::ExternalFileName, "ExternalFileName", "External File Name"},
{ Table_MultiVariableLookupFields::X1SortOrder, "X1SortOrder", "X1 Sort Order"},
{ Table_MultiVariableLookupFields::X2SortOrder, "X2SortOrder", "X2 Sort Order"},
{ Table_MultiVariableLookupFields::NormalizationReference, "NormalizationReference", "Normalization Reference"},
{ Table_MultiVariableLookupFields::MinimumValueofX1, "MinimumValueofX1", "Minimum Value of X1"},
{ Table_MultiVariableLookupFields::MaximumValueofX1, "MaximumValueofX1", "Maximum Value of X1"},
{ Table_MultiVariableLookupFields::MinimumValueofX2, "MinimumValueofX2", "Minimum Value of X2"},
{ Table_MultiVariableLookupFields::MaximumValueofX2, "MaximumValueofX2", "Maximum Value of X2"},
{ Table_MultiVariableLookupFields::MinimumValueofX3, "MinimumValueofX3", "Minimum Value of X3"},
{ Table_MultiVariableLookupFields::MaximumValueofX3, "MaximumValueofX3", "Maximum Value of X3"},
{ Table_MultiVariableLookupFields::MinimumValueofX4, "MinimumValueofX4", "Minimum Value of X4"},
{ Table_MultiVariableLookupFields::MaximumValueofX4, "MaximumValueofX4", "Maximum Value of X4"},
{ Table_MultiVariableLookupFields::MinimumValueofX5, "MinimumValueofX5", "Minimum Value of X5"},
{ Table_MultiVariableLookupFields::MaximumValueofX5, "MaximumValueofX5", "Maximum Value of X5"},
{ Table_MultiVariableLookupFields::MinimumTableOutput, "MinimumTableOutput", "Minimum Table Output"},
{ Table_MultiVariableLookupFields::MaximumTableOutput, "MaximumTableOutput", "Maximum Table Output"},
{ Table_MultiVariableLookupFields::InputUnitTypeforX1, "InputUnitTypeforX1", "Input Unit Type for X1"},
{ Table_MultiVariableLookupFields::InputUnitTypeforX2, "InputUnitTypeforX2", "Input Unit Type for X2"},
{ Table_MultiVariableLookupFields::InputUnitTypeforX3, "InputUnitTypeforX3", "Input Unit Type for X3"},
{ Table_MultiVariableLookupFields::InputUnitTypeforX4, "InputUnitTypeforX4", "Input Unit Type for X4"},
{ Table_MultiVariableLookupFields::InputUnitTypeforX5, "InputUnitTypeforX5", "Input Unit Type for X5"},
{ Table_MultiVariableLookupFields::OutputUnitType, "OutputUnitType", "Output Unit Type"},
{ Table_MultiVariableLookupFields::NumberofIndependentVariables, "NumberofIndependentVariables", "Number of Independent Variables"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_MultiVariableLookupFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_MultiVariableLookupFields> OptionalTable_MultiVariableLookupFields ;
#endif

/** \class Table_MultiVariableLookupExtensibleFields
 *  \brief Enumeration of Table:MultiVariableLookup's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(Table_MultiVariableLookupExtensibleFields, )
#else
class Table_MultiVariableLookupExtensibleFields: public ::EnumBase<Table_MultiVariableLookupExtensibleFields> {
 public: 
  enum domain 
  {
Data,   };
  Table_MultiVariableLookupExtensibleFields()
   : EnumBase<Table_MultiVariableLookupExtensibleFields>(Data) {} 
  Table_MultiVariableLookupExtensibleFields(const std::string &t_name) 
   : EnumBase<Table_MultiVariableLookupExtensibleFields>(t_name) {} 
  Table_MultiVariableLookupExtensibleFields(int t_value) 
   : EnumBase<Table_MultiVariableLookupExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "Table_MultiVariableLookupExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<Table_MultiVariableLookupExtensibleFields>::value()); }
   private:
    friend class EnumBase<Table_MultiVariableLookupExtensibleFields>;
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
{ Table_MultiVariableLookupExtensibleFields::Data, "Data", "Data"},
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
  inline std::ostream &operator<<(std::ostream &os, const Table_MultiVariableLookupExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<Table_MultiVariableLookupExtensibleFields> OptionalTable_MultiVariableLookupExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_TABLE_MULTIVARIABLELOOKUP_FIELDENUMS_HXX
