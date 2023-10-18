## What is SDN?

Routing through a network has traditionally been handled by dedicated hardware such as routers and switches. SDN moves these functions into software, providing a mechanism by which network control logic is decoupled from the device that implements it. SDN layers software controllers atop your hardware so you can dynamically define network behavior as sets of rules and policies. The network becomes more flexible because you can change its configuration on demand without requiring additional, or altering existing, hardware.

As an administrator, you get to oversee the network using a centralized interface and make adjustments to your network topography on the fly. You can set up new routes, manage bandwidth controls, and monitor health without having to install or connect to individual pieces of hardware. The software controller automatically applies your changes across the infrastructure.

SDN only changes where routing decisions are made; the actual data transfer is still handled by the networking hardware, as it always has been. The router or switch verifies the packets for integrity before redirecting them to the destination indicated by the controller software.

## Common SDN use cases

With the opportunities it offers to make networks more configurable and efficient, it’s no wonder SDN adoption is growing. Here are some of the more common use cases.

### Centralized network control

SDN should always be a contender when you need centralized control of a network and its components. A software-based approach lets you make changes to your architecture selectively, without having to interact with the underlying hardware. You can dynamically adjust your network to support new applications and devices as they come online.

### Abstracting network functions

SDN abstracts network operation from its configuration. Applications that are connected using SDN components sit separately from the low-level technologies and infrastructure resources that create the physical network. This can make it easier to swap out specific pieces in the future without compromising the network configuration.

### Distributed networking

SDN supports distributed networking tasks such as edge computing, the Internet of Things (IoT), and remote user access. The centralized control plane means new devices can be onboarded without compromising reliability, security, or ease of management.

## The benefits of SDN

SDN provides agility and flexibility when routing data through networks. Routing decisions can be centralized, changed, and monitored without affecting performance or efficiency. The logic of working out how to handle a data packet is separated from the action of moving it through the infrastructure.

This abstraction of control helps administrators dynamically adjust their network’s parameters in response to changing traffic requirements. Communication between components is achieved using standardized APIs that simplify network implementation and operation.

SDN’s ability to adapt in real time also makes it well suited to emerging technologies such as IoT. Distributed devices that are networked using LTE and 5G need to rapidly transfer data between locations while remaining resilient to changing network conditions.

## The drawbacks of SDN

Because SDN is still relatively new, there are aspects that could be improved. You may struggle to find reference implementations or hire staff that are trained in relevant technologies. SDN also requires you to learn new management tools for configuring and monitoring your network.

Security is another big concern. Moving routing into software creates a new attack vector. A successful compromise of your SDN controller would expose your network’s architecture and prevent devices from receiving their config policies. You must ensure that access to your SDN system is restricted to essential users.

SDN can create new failure points in your network, too. The SDN controller is a particular weak spot as its loss could destroy network connectivity. Researching the reliability of your chosen SDN solution before you start your deployment is a good idea. It’s also worth rehearsing how you’d respond to an unresponsive or malfunctioning controller.

## SDN architecture

SDN architecture comprises three main components: the application, the SDN controller, and the physical network devices that ultimately route packets.

### SDN applications

The application layer is responsible for communicating new routing requests. Applications might also monitor broader information about the network, such as its available capacity. Administrators use the application layer to apply new configurations and interact with the network.

### SDN controllers

Controllers receive routing requests from the application layer. They use the available rules to decide each data packet’s destination. Although this layer determines how to route traffic, it doesn’t actually move any data through the network.

### Networking devices

The physical networking devices in your infrastructure communicate with your SDN controllers to action new routing requests. The device honors the decision made by the SDN controller and causes the data packet to be forwarded along the correct network pathway. The device could incorporate some protections to ensure it’s sending traffic to an accessible destination.

## How data flows through the architecture

Data moves between applications, controllers, and physical devices using well-defined APIs. The two different layers are sometimes referred to using “northbound” and “southbound” terminology. This describes how dynamic rule changes made by administrators are communicated first to the network controller and then to the physical routers and switches.

Northbound APIs sit between applications and controllers. They allow applications to inform the network of new requirements, such as bandwidth requests and new routing rules. The controllers will relay information back to the application to confirm changes have been applied and report any errors.

Southbound APIs form the mesh between controllers and hardware. They let controllers influence the operation of physical devices to enact changes requested by the northbound APIs. Southbound APIs can be open source or proprietary solutions offered by individual hardware vendors.

## Reference

[Understanding software-defined networking](https://tailscale.com/learn/software-defined-networking) by James Walker
