the control plane corresponds to the background processing required to “control” the network (e.g., running OSPF, RIP, or the BGP protocol) and the data plane corresponds to the per-packet processing required to move packets from input port to output port. For historical reasons, this distinction is called control plane and user plane in cellular access networks, but the idea is the same

The main differences between control and data planes are their purpose and how they communicate between different systems. The control plane decides how data is managed, routed, and processed, while the data plane is responsible for the actual moving of data. For example, the control plane decides how packets should be routed, and the data plane carries out those instructions by forwarding the packets.

Along with doing different jobs, control planes and data planes exist in different areas. While the control plane runs in the cloud, the data plane runs in the data processing area.

They also use different functions to do their jobs. Control planes use protocols to communicate between different systems, mostly common routing protocols like BGP, OSPF, and IS-IS or network management protocols like SNMP. These protocols enable the control plane to make decisions on how data should be managed, routed, and processed.

Data planes use dedicated networks to communicate between different systems. Examples of dedicated networks used in data planes include Ethernet and Wi-Fi networks, cellular networks, satellite communications, virtualized networks, and dedicated networks used in industrial control systems or IoT. These networks enable the data plane to deliver data to end users from systems and vice versa.
