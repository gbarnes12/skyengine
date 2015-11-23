using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace skySuite.DataLists
{
    public class skyLogList : List<skyLogEntry>
    {
        public skyLogList()
        {
        }

        public new void Add(skyLogEntry a_cEntry)
        {
            base.Add(a_cEntry);
        }
    }
}
