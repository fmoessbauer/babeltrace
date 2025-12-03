# SPDX-License-Identifier: GPL-2.0-only
#
# Copyright (C) 2025 Siemens
#

import bt2


class TheSourceIterator(bt2._UserMessageIterator):
    """
    Creates a message stream as following, whereby packets are only
    created if the with-packet-msgsinput parameter is set.
    [packet]
      the-event
      the-event
    [packet]
      the-event
    """
    def __init__(self, config, port):
        tc, sc, ec, params = port.user_data

        trace = tc()
        stream = trace.create_stream(sc, name="the-stream")

        self._msgs = []
        self._msgs.append(self._create_stream_beginning_message(stream))

        if params["with-packet-msgs"]:
            packet = stream.create_packet()
            packet.context_field["cpu_id"] = 0
            self._msgs.append(self._create_packet_beginning_message(packet))

        parent = packet if params["with-packet-msgs"] else stream

        self._msgs.append(self._create_event_message(ec, parent))
        self._msgs.append(self._create_event_message(ec, parent))

        if params["with-packet-msgs"]:
            self._msgs.append(self._create_packet_end_message(parent))
            self._msgs.append(self._create_packet_beginning_message(parent))

        self._msgs.append(self._create_event_message(ec, parent))

        if params["with-packet-msgs"]:
            self._msgs.append(self._create_packet_end_message(parent))

        self._msgs.append(self._create_stream_end_message(stream))

    def __next__(self):
        if len(self._msgs) == 0:
            raise StopIteration

        return self._msgs.pop(0)


@bt2.plugin_component_class
class TheSource(bt2._UserSourceComponent, message_iterator_class=TheSourceIterator):
    def __init__(self, config, params, obj):
        tc = self._create_trace_class()

        with_packets = bool(params["with-packet-msgs"])

        if with_packets:
            sc = tc.create_stream_class(
                supports_packets=True,
                packet_context_field_class=tc.create_structure_field_class(
                    members=[("cpu_id", tc.create_unsigned_integer_field_class())]
                ),
            )
        else:
            sc = tc.create_stream_class()

        ec = sc.create_event_class(name="the-event")
        self._add_output_port("out", user_data=(tc, sc, ec, params))


bt2.register_plugin(__name__, "foo")
