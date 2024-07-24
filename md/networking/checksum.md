why UDP provides a checksum in the first place, as many link-layer protocols (including the popular Ethernet protocol) also provide error
checking. The reason is that there is no guarantee that all the links between source
and destination provide error checking; that is, one of the links may use a link-layer
protocol that does not provide error checking. Furthermore, even if segments are
correctly transferred across a link, it’s possible that bit errors could be introduced
when a segment is stored in a router’s memory.