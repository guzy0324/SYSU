pragma solidity>=0.4.24;

contract Upvote
{
    struct User
    {
        uint votes;
        bool given;
    }

    struct Content
    {
        string name;
        uint votes;
    }

    address public publisher;
    mapping(address => User) public users;
    Content[] public contents;

    constructor() public
    {
        publisher = msg.sender;
    }

    function publish(string memory name) public
    {
        require(msg.sender == publisher, "Only the publisher can publish contents.");
        for (uint i = 0; i < contents.length; i++)
        {
            require(keccak256(name) != keccak256(contents[i].name), "The content already exists.");
        }
        contents.push(Content({name: name, votes: 0}));
    }

    function giveVotesToUser(address user) public
    {
        require(msg.sender == publisher, "Only the publisher can give votes to a user.");
        require(users[user].given == false, "The user has been given votes.");
        users[user].votes = 10;
    }

    function upvote(string memory name, uint votes) public
    {
        User storage sender = users[msg.sender];
        require(sender.votes >= votes, "Don't have enough votes.");
        uint i = 0;
        for (; i < contents.length; i++)
        {
            if (keccak256(name) == keccak256(contents[i].name))
            {
                sender.votes -= votes;
                contents[i].votes += votes;
                break;
            }
        }
        require(i < contents.length, "The content doesn't exist.");
    }

    function winner() public view returns(string memory)
    {
        uint max_votes = 0;
        string storage name;
        for (uint i = 0; i < contents.length; i++)
        {
            if (max_votes < contents[i].votes)
            {
                max_votes = contents[i].votes;
                name = contents[i].name;
            }
        }
        return name;
    }
}