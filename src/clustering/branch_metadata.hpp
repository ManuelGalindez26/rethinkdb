

template<class protocol_t>
struct branch_metadata_t {

    /* The initial state of the branch is composed of these regions of these
    versions. */

    std::vector<std::pair<typename protocol_t::region_t, version_t> > parents;

    /* If `alive` is `false`, then the branch is defunct, the master no longer
    exists, and all the master-mailboxes are nil. */

    bool is_alive;

    /* These are the mailboxes to send reads and writes to if you want to
    operate on the branch. */

    typedef async_mailbox_t<void(
        typename protocol_t::read_t, order_token_t,
        async_mailbox_t<void(typename protocol_t::read_response_t)>::address_t
        )> read_mailbox_t;
    read_mailbox_t::address_t read_mailbox;

    typedef async_mailbox_t<void(
        typename protocol_t::write_t, order_token_t,
        async_mailbox_t<void(typename protocol_t::write_response_t)>::address_t
        )> write_mailbox_t;
    write_mailbox_t::address_t write_mailbox;

    /* These are the mirrors that the branch has. */

    typedef boost::uuids::uuid mirror_id_t;
    std::map<mirror_id_t, backfiller_metadata_t<protocol_t> > mirrors;

    /* This is how mirrors get in touch with the master when they start up */

    registrar_metadata_t<protocol_t> registrar;
};

