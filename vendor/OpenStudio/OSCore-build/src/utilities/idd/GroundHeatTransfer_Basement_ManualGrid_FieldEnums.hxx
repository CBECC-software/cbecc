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

#ifndef UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_MANUALGRID_FIELDENUMS_HXX
#define UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_MANUALGRID_FIELDENUMS_HXX

#include <utilities/UtilitiesAPI.hpp>
#include <utilities/core/Enum.hpp>

namespace openstudio {
/** \class GroundHeatTransfer_Basement_ManualGridFields
 *  \brief Enumeration of GroundHeatTransfer:Basement:ManualGrid's Idd and Idf non-extensible fields. 
 *  \details This enumeration provides readable, and semi-robust tags to use instead
 *  of bare unsigned integer field indices. (The enumeration value names are more likely
 *  to be valid across EnergyPlus and OpenStudio releases, and will break if they become
 *  invalid.) See the OPENSTUDIO_ENUM documentation in utilities/core/Enum.hpp. The actual macro
 *  call is:
 *
 *  \code
 *  \endcode */
#ifdef SWIG 
  OPENSTUDIO_ENUM(GroundHeatTransfer_Basement_ManualGridFields, )
#else
class GroundHeatTransfer_Basement_ManualGridFields: public ::EnumBase<GroundHeatTransfer_Basement_ManualGridFields> {
 public: 
  enum domain 
  {
NX_NumberofcellsintheXdirection_20, NY_NumberofcellsintheYdirection_20, NZAG_NumberofcellsintheZdirectionabovegrade_4Always, NZBG_NumberofcellsinZdirectionbelowgrade_1035, IBASE_Xdirectioncellindicatorofslabedge_520, JBASE_Ydirectioncellindicatorofslabedge_520, KBASE_Zdirectioncellindicatorofthetopofthefloorslab_520,   };
  GroundHeatTransfer_Basement_ManualGridFields()
   : EnumBase<GroundHeatTransfer_Basement_ManualGridFields>(NX_NumberofcellsintheXdirection_20) {} 
  GroundHeatTransfer_Basement_ManualGridFields(const std::string &t_name) 
   : EnumBase<GroundHeatTransfer_Basement_ManualGridFields>(t_name) {} 
  GroundHeatTransfer_Basement_ManualGridFields(int t_value) 
   : EnumBase<GroundHeatTransfer_Basement_ManualGridFields>(t_value) {} 
  static std::string enumName() 
  { return "GroundHeatTransfer_Basement_ManualGridFields"; }
  domain value() const { return static_cast<domain>(EnumBase<GroundHeatTransfer_Basement_ManualGridFields>::value()); }
   private:
    friend class EnumBase<GroundHeatTransfer_Basement_ManualGridFields>;
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
{ GroundHeatTransfer_Basement_ManualGridFields::NX_NumberofcellsintheXdirection_20, "NX_NumberofcellsintheXdirection_20", "NX: Number of cells in the X direction: 20]"},
{ GroundHeatTransfer_Basement_ManualGridFields::NY_NumberofcellsintheYdirection_20, "NY_NumberofcellsintheYdirection_20", "NY: Number of cells in the Y direction: 20]"},
{ GroundHeatTransfer_Basement_ManualGridFields::NZAG_NumberofcellsintheZdirectionabovegrade_4Always, "NZAG_NumberofcellsintheZdirectionabovegrade_4Always", "NZAG: Number of cells in the Z direction. above grade: 4 Always]"},
{ GroundHeatTransfer_Basement_ManualGridFields::NZBG_NumberofcellsinZdirectionbelowgrade_1035, "NZBG_NumberofcellsinZdirectionbelowgrade_1035", "NZBG: Number of cells in Z direction. below grade: 10-35]"},
{ GroundHeatTransfer_Basement_ManualGridFields::IBASE_Xdirectioncellindicatorofslabedge_520, "IBASE_Xdirectioncellindicatorofslabedge_520", "IBASE: X direction cell indicator of slab edge: 5-20]"},
{ GroundHeatTransfer_Basement_ManualGridFields::JBASE_Ydirectioncellindicatorofslabedge_520, "JBASE_Ydirectioncellindicatorofslabedge_520", "JBASE: Y direction cell indicator of slab edge: 5-20]"},
{ GroundHeatTransfer_Basement_ManualGridFields::KBASE_Zdirectioncellindicatorofthetopofthefloorslab_520, "KBASE_Zdirectioncellindicatorofthetopofthefloorslab_520", "KBASE: Z direction cell indicator of the top of the floor slab: 5-20]"},
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
  inline std::ostream &operator<<(std::ostream &os, const GroundHeatTransfer_Basement_ManualGridFields &e)
  {
    return os << e.valueName() << "(" << e.value() << ")";
  }
  typedef boost::optional<GroundHeatTransfer_Basement_ManualGridFields> OptionalGroundHeatTransfer_Basement_ManualGridFields ;
#endif

} // openstudio

#endif // UTILITIES_IDD_GROUNDHEATTRANSFER_BASEMENT_MANUALGRID_FIELDENUMS_HXX
