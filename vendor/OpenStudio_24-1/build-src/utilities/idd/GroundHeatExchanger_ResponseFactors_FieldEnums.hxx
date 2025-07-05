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

#ifndef UTILITIES_IDD_GROUNDHEATEXCHANGER_RESPONSEFACTORS_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATEXCHANGER_RESPONSEFACTORS_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatExchanger_ResponseFactorsFields
 *  \brief Enumeration of GroundHeatExchanger:ResponseFactors's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatExchanger_ResponseFactorsFields, )
#else
class GroundHeatExchanger_ResponseFactorsFields: public ::EnumBase<GroundHeatExchanger_ResponseFactorsFields> {
 public: 
  enum domain 
  {
Name, GHE_Vertical_PropertiesObjectName, NumberofBoreholes, GFunctionReferenceRatio,   };
  GroundHeatExchanger_ResponseFactorsFields()
   : EnumBase<GroundHeatExchanger_ResponseFactorsFields>(Name) {} 
  GroundHeatExchanger_ResponseFactorsFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsFields>(t_name) {} 
  GroundHeatExchanger_ResponseFactorsFields(int t_value) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_ResponseFactorsFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_ResponseFactorsFields>::value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_ResponseFactorsFields>;
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
{ GroundHeatExchanger_ResponseFactorsFields::Name, "Name", "Name"},
{ GroundHeatExchanger_ResponseFactorsFields::GHE_Vertical_PropertiesObjectName, "GHE_Vertical_PropertiesObjectName", "GHE:Vertical:Properties Object Name"},
{ GroundHeatExchanger_ResponseFactorsFields::NumberofBoreholes, "NumberofBoreholes", "Number of Boreholes"},
{ GroundHeatExchanger_ResponseFactorsFields::GFunctionReferenceRatio, "GFunctionReferenceRatio", "G-Function Reference Ratio"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_ResponseFactorsFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_ResponseFactorsFields> OptionalGroundHeatExchanger_ResponseFactorsFields ;
#endif

/** \class GroundHeatExchanger_ResponseFactorsExtensibleFields
 *  \brief Enumeration of GroundHeatExchanger:ResponseFactors's Idd and Idf extensible fields
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
  OPENSTUDIO_ENUM(GroundHeatExchanger_ResponseFactorsExtensibleFields, )
#else
class GroundHeatExchanger_ResponseFactorsExtensibleFields: public ::EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields> {
 public: 
  enum domain 
  {
gFunctionLn_T_Ts_Value, gFunctiongValue,   };
  GroundHeatExchanger_ResponseFactorsExtensibleFields()
   : EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>(gFunctionLn_T_Ts_Value) {} 
  GroundHeatExchanger_ResponseFactorsExtensibleFields(const std::string &t_name) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>(t_name) {} 
  GroundHeatExchanger_ResponseFactorsExtensibleFields(int t_value) 
   : EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatExchanger_ResponseFactorsExtensibleFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>::value()); }
   private:
    friend class EnumBase<GroundHeatExchanger_ResponseFactorsExtensibleFields>;
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
{ GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctionLn_T_Ts_Value, "gFunctionLn_T_Ts_Value", "g-Function Ln(T/Ts) Value"},
{ GroundHeatExchanger_ResponseFactorsExtensibleFields::gFunctiongValue, "gFunctiongValue", "g-Function g Value"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatExchanger_ResponseFactorsExtensibleFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatExchanger_ResponseFactorsExtensibleFields> OptionalGroundHeatExchanger_ResponseFactorsExtensibleFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATEXCHANGER_RESPONSEFACTORS_FIELDENUMS_HXX
